package net.fortune;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;
import com.google.gson.stream.JsonReader;
import net.fortune.entities.CarModel;
import net.fortune.entities.Maker;
import net.fortune.entities.TrimLevel;

import java.io.*;
import java.lang.reflect.Type;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import java.util.List;

public class JsonProcessor {

    public static List<Maker> deserializeFromJson(Path filePath) throws FileNotFoundException {

        Type makersType = new TypeToken<List<Maker>>() {}.getType();
        Gson gson = new Gson();
        JsonReader reader = new JsonReader(new FileReader(filePath.toString()));

        return gson.fromJson(reader, makersType);
    }

    public static void serializeToJson(Path filePath, List<CarModel> carModels) throws IOException {

        Gson gson = new GsonBuilder().serializeNulls().setPrettyPrinting().create();

        Type modelsType = new TypeToken<List<CarModel>>() {}.getType();

        // Serialization
        try (Writer writer = new FileWriter(filePath.toString(), StandardCharsets.UTF_8)) {
            gson.toJson(carModels, modelsType, writer);
        }
    }

    public static List<CarModel> deserializeCarModelsFromJson(Path filePath) throws FileNotFoundException {

        Type makersType = new TypeToken<List<CarModel>>() {}.getType();
        Gson gson = new Gson();
        JsonReader reader = new JsonReader(new FileReader(filePath.toString()));

        return gson.fromJson(reader, makersType);
    }

    public static void serializeLevelsToJson(Path filePath, List<TrimLevel> levels) throws IOException {

        Gson gson = new GsonBuilder().serializeNulls().setPrettyPrinting().create();

        Type levelsType = new TypeToken<List<TrimLevel>>() {}.getType();

        // Serialization
        try (Writer writer = new FileWriter(filePath.toString(), StandardCharsets.UTF_8)) {
            gson.toJson(levels, levelsType, writer);
        }
    }

}
