package combinatorpatterns;

import java.time.LocalDate;

public class Main {
    public static void main(String[] args) {
        Customer customer = new Customer(
                "Alice",
                "alice@gmail.com",
                "+0123456789",
                LocalDate.of(2000,1,1)
        );

        // normal function approach
        System.out.println(new CustomerValidatorService().isValid(customer));

        // using combinator pattern
        CustomerRegistrationValidator.ValidationResult result = CustomerRegistrationValidator
                .isEmailValid()
                .and(CustomerRegistrationValidator.isPhoneNumberValid())
                .and(CustomerRegistrationValidator.isAdult())
                .apply(customer);

        // can be lazy, only call apply will actually run

        System.out.println(result);

        if (result != CustomerRegistrationValidator.ValidationResult.SUCCESS){
            throw new IllegalStateException(result.name());
        }

    }
}
