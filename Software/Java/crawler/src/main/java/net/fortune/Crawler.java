package net.fortune;

import net.fortune.entities.CarModel;
import net.fortune.entities.Maker;
import net.fortune.entities.TrimLevel;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

public class Crawler {

    static String _makersJsonFile = "D:\\CodingWorkspace\\Github\\YamanoProject\\crawler\\automobile\\data\\UcarManufacturers.json";
    static String _modelsJsonFile = "D:\\CodingWorkspace\\Github\\PieceNote\\Software\\Java\\AllModels.json";
    static String _levelsJsonFile = "D:\\CodingWorkspace\\Github\\PieceNote\\Software\\Java\\AllLevels.json";
    static String _modelsOfNewReleasedJsonFile = "D:\\CodingWorkspace\\Github\\PieceNote\\Software\\Java\\NewReleaseModels.json";
    static String _levelsOfNewReleasedJsonFile = "D:\\CodingWorkspace\\Github\\PieceNote\\Software\\Java\\NewReleaseLevels.json";

    public static void main(String[] args) {

        try {

            // makers -> models
            GetModelsFromMakers(_makersJsonFile, _modelsJsonFile);

            // models -> levels
            GetLevelsFromModels(_modelsJsonFile, _levelsJsonFile);
//            GetLevelsFromModels(_modelsOfNewReleasedJsonFile, _levelsOfNewReleasedJsonFile);


        } catch (Exception e) {
            e.printStackTrace();
        } finally {

        }
    }

    private static void GetModelsFromMakers(String srcMakersFile, String destModelsFile) throws IOException {
        List<Maker> makers = JsonProcessor.deserializeFromJson(Paths.get(srcMakersFile));

        List<CarModel> allModels = new ArrayList<>();
//            for (Maker maker : makers) {
        for (Maker maker : makers.subList(0,1)) {


            try {
                System.out.println(new StringBuilder().append("Start process: ").append(maker));
                List<CarModel> modelsOfMaker = UcarWebProcessor.getModelsOf(maker);
                allModels.addAll(modelsOfMaker);
            } catch (IOException e) {
                e.printStackTrace();
            } catch (Exception e) {
                System.out.println(new StringBuilder().append("  Maker: ").append(maker.getName()).append("failed...").append(e));
            }
        }

        JsonProcessor.serializeToJson(Paths.get(destModelsFile), allModels);
    }

    private static void GetLevelsFromModels(String srcModelsFile, String destLevelsFile) {
        try {
            List<CarModel> models = JsonProcessor.deserializeCarModelsFromJson(Paths.get(srcModelsFile));

            List<TrimLevel> allLevels = new ArrayList<>();
//            for (CarModel model : models) {
            for (CarModel model : models.subList(0,2)) {
                try {
                    System.out.println(new StringBuilder().append("Start process: ").append(model.getManufacturerId()).append("-").append(model));
                    List<TrimLevel> levelsOfModel = UcarWebProcessor.getLevelsOf(model);
                    allLevels.addAll(levelsOfModel);
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (Exception e) {
                    System.out.println(new StringBuilder().append("  Model: ").append(model.getName()).append("failed...").append(e));
                }
            }

            JsonProcessor.serializeLevelsToJson(Paths.get(destLevelsFile), allLevels);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
