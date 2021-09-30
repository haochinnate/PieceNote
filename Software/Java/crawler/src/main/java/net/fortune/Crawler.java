package net.fortune;

import net.fortune.entities.CarModel;
import net.fortune.entities.Maker;
import net.fortune.entities.TrimLevel;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;

public class Crawler {

    static String _makersJsonFile = "D:\\CodingWorkspace\\Github\\YamanoProject\\crawler\\automobile\\data\\UcarManufacturers.json";
    static String _modelsJsonFile = "D:\\CodingWorkspace\\Github\\PieceNote\\Software\\Java\\AllModels.json";
    static String _levelsJsonFile = "D:\\CodingWorkspace\\Github\\PieceNote\\Software\\Java\\AllLevels.json";
    static String _modelsOfNewReleasedJsonFile = "D:\\CodingWorkspace\\Github\\PieceNote\\Software\\Java\\NewReleaseModels.json";
    static String _levelsOfNewReleasedJsonFile = "D:\\CodingWorkspace\\Github\\PieceNote\\Software\\Java\\NewReleaseLevels.json";
    static int _threadPoolSize = 8;

    public static void main(String[] args) {

        try {

            // makers -> models
//            GetModelsFromMakers(_makersJsonFile, _modelsJsonFile);
            getModelsFromMakersAsync(_makersJsonFile, _modelsJsonFile);


            // models -> levels
//            GetLevelsFromModels(_modelsJsonFile, _levelsJsonFile);
//            GetLevelsFromModels(_modelsOfNewReleasedJsonFile, _levelsOfNewReleasedJsonFile);


        } catch (Exception e) {
            e.printStackTrace();
        } finally {

        }
    }

    private static void GetModelsFromMakers(String srcMakersFile, String destModelsFile) throws IOException {
        long startTime = System.nanoTime();

        List<Maker> makers = JsonProcessor.deserializeFromJson(Paths.get(srcMakersFile));

        List<CarModel> allModels = new ArrayList<>();
        for (Maker maker : makers) {
//        for (Maker maker : makers.subList(0,1)) {
            try {
//                System.out.println(new StringBuilder().append("Start process: ").append(maker));
                List<CarModel> modelsOfMaker = UcarWebProcessor.getModelsOf(maker);
                allModels.addAll(modelsOfMaker);
            } catch (IOException e) {
                e.printStackTrace();
            } catch (Exception e) {
                System.out.println(new StringBuilder().append("  Maker: ").append(maker.getName()).append(" failed...").append(e));
            }
        }

        JsonProcessor.serializeToJson(Paths.get(destModelsFile), allModels);

        long endTime = System.nanoTime();
        System.out.println("Process makers took: " + (endTime - startTime)/1000000 + " milliseconds");
    }

    private static void GetLevelsFromModels(String srcModelsFile, String destLevelsFile) {
        long startTime = System.nanoTime();

        try {
            List<CarModel> models = JsonProcessor.deserializeCarModelsFromJson(Paths.get(srcModelsFile));

            List<TrimLevel> allLevels = new ArrayList<>();
            for (CarModel model : models) {
//            for (CarModel model : models.subList(0,2)) {
                try {
//                    System.out.println(new StringBuilder().append("Start process: ").append(model.getManufacturerId()).append("-").append(model));
                    List<TrimLevel> levelsOfModel = UcarWebProcessor.getLevelsOf(model);
                    allLevels.addAll(levelsOfModel);
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (Exception e) {
                    System.out.println(new StringBuilder().append("  Model: ").append(model.getName()).append(" failed...").append(e));
                }
            }

            JsonProcessor.serializeLevelsToJson(Paths.get(destLevelsFile), allLevels);

        } catch (IOException e) {
            e.printStackTrace();
        }

        long endTime = System.nanoTime();
        System.out.println("Process models took: " + (endTime - startTime)/1000000 + " milliseconds");
    }

    private static void getModelsFromMakersAsync(String srcMakersFile, String destModelsFile) throws IOException, ExecutionException, InterruptedException {
//            Map<String, List<String>> campaignIdsByAccount, JobMetrics metrics, Function<Map.Entry<String, List<String>>, Void> function) {

        long startTime = System.nanoTime();

        List<Maker> makers = JsonProcessor.deserializeFromJson(Paths.get(srcMakersFile));
//        List<CarModel> allModels = new ArrayList<>();

        ExecutorService threadPool = Executors.newFixedThreadPool(_threadPoolSize);

//        List<CompletableFuture<List<CarModel>>> completableFutures = makers.subList(0,3).stream().map(maker -> CompletableFuture
//                .supplyAsync(() -> {
//                    List<CarModel> modelsOfMaker = new ArrayList<>();
//                    try {
//                        System.out.println("current process: " + maker);
//                        modelsOfMaker = UcarWebProcessor.getModelsOf(maker);
//                    } catch (IOException e) {
//                        e.printStackTrace();
//                    }
//                    return modelsOfMaker;
//                }, threadPool)
//        ).collect(Collectors.toList());

        List<CompletableFuture<List<CarModel>>> completableFutures = makers.stream().map(maker -> CompletableFuture
                .supplyAsync(() -> {
                    List<CarModel> modelsOfMaker = new ArrayList<>();
                    try {
                        System.out.println("current process: " + maker);
                        modelsOfMaker = UcarWebProcessor.getModelsOf(maker);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    return modelsOfMaker;
                }, threadPool)
//                .whenComplete((result, ex) -> {
//                    allModels.addAll(result);
//                })
        ).collect(Collectors.toList());



        // Create a combined Future using allOf()
        CompletableFuture<Void> allFutures = CompletableFuture.allOf(
                completableFutures.toArray(new CompletableFuture[completableFutures.size()])
        );

//        allFutures.complete(true);
        allFutures.get();


        // When all the Futures are completed, call `future.join()` to get their results and collect the results in a list -
        CompletableFuture<List<List<CarModel>>> allPageContentsFuture = allFutures.thenApply(v -> {
            return completableFutures.stream()
                    .map(oneFuture -> oneFuture.join())
                    .collect(Collectors.toList());
        });

        List<List<CarModel>> allModelsByMaker = allPageContentsFuture.get();

        List<CarModel> allModels = allModelsByMaker
                .stream()
                .flatMap(listContainer -> listContainer.stream())
                .collect(Collectors.toList());

        AtomicInteger atomicInteger = new AtomicInteger(0);
        allModels.stream().forEach(model -> model.setId(atomicInteger.getAndIncrement()));

        // to json file
        JsonProcessor.serializeToJson(Paths.get(destModelsFile), allModels);

        long endTime = System.nanoTime();
        System.out.println("Process makers took: " + (endTime - startTime)/1000000 + " milliseconds");

        return;
    }

    private static void getLevelsFromModelsAsync(String srcModelsFile, String destLevelsFile) {

    }
}
