package finalsection;

import java.util.function.BiFunction;
import java.util.function.Consumer;
import java.util.function.Function;

public class Lambdas {
    public static void main(String[] args) {

        Function<String, String> upperCaseName = name -> {
            // logic
            if (name.isBlank()) throw new IllegalArgumentException("");
            return name.toUpperCase();
        };

        BiFunction<String, Integer, String> twoArgsFunction = (name, age) -> {
            System.out.println(name + age);
            return name + age;
        };

        upperCaseName.apply("Alex");
        twoArgsFunction.apply("Livia", 28);

    }
}
