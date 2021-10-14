package functionalinterface;

import java.util.List;
import java.util.function.Supplier;

public class _Supplier {
    public static void main(String[] args) {

        // normal function
        System.out.println(getDbConnectionUrl());

        // supplier
        System.out.println(getDbConnectionUrlSupplier2.get());
    }

    static Supplier<String> getDbConnectionUrlSupplier = ()
            -> "jdbc://localhost:5432/users";

    static Supplier<List<String>> getDbConnectionUrlSupplier2 = ()
            -> List.of("jdbc://localhost:5432/users");

    static String getDbConnectionUrl() {
        return "jdbc://localhost:5432/users";
    }

}
