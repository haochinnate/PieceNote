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
//            String modelsToUpdateJsonFile = "D:\\CodingWorkspace\\Github\\PieceNote\\Software\\Java\\ModelsToUpdate.json";


    public static void main(String[] args) {

        try {

            // makers -> models
//            GetModelsFromMakers();

            // models -> levels
            GetLevelsFromModels(_modelsJsonFile);


        } catch (Exception e) {
            e.printStackTrace();
        } finally {

        }
    }

    private static void GetModelsFromMakers() throws IOException {
        List<Maker> makers = JsonProcessor.deserializeFromJson(Paths.get(_makersJsonFile));

        List<CarModel> allModels = new ArrayList<>();
//            for (Maker maker : makers) {
        for (Maker maker : makers.subList(0,1)) {
            System.out.println(maker.toString());
            List<CarModel> modelsOfMaker = UcarWebProcessor.getModelsOf(maker);
            allModels.addAll(modelsOfMaker);
        }

        JsonProcessor.serializeToJson(Paths.get(_modelsJsonFile), allModels);
    }

    private static void GetLevelsFromModels(String modelsJsonFile) {
        try {
            List<CarModel> models = JsonProcessor.deserializeCarModelsFromJson(Paths.get(modelsJsonFile));

            List<TrimLevel> allLevels = new ArrayList<>();
//            for (CarModel model : models) {
            for (CarModel model : models.subList(0,2)) {
                System.out.println("Start process: " + model.getManufacturerId() + "-" + model.toString());
                List<TrimLevel> levelsOfModel = UcarWebProcessor.getLevelsOf(model);
//                allLevels.addAll(levelsOfModel);
            }

//            JsonProcessor.serializeToJson(Paths.get(_modelsJsonFile), allModels);



        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
