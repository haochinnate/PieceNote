package optionals;

import java.util.Optional;

public class Main {
    public static void main(String[] args) {
        Object value = Optional.ofNullable(null)
                .orElseGet(() -> "default value");
        System.out.println(value);

        Object value2 = Optional.ofNullable("hello")
                .orElseThrow(() -> new IllegalStateException("exception"));
        System.out.println(value2);

        Optional.ofNullable(null)
                .ifPresentOrElse(
                        text -> System.out.println("iterative " + text),
                        () -> {
                            System.out.println("error");
                        });

    }
}
