package com.qineria.Fortune;

import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import static org.assertj.core.api.AssertionsForClassTypes.assertThat;

class FortuneApplicationTests {

	Calculator underTest = new Calculator();

	@Test
	void itShouldAddTwoNumbers() {
		// given
		int numberOne = 20;
		int numberTwo = 40;

		// when
		int result = underTest.add(numberOne, numberTwo);

		// then
		int expected = 60;
		assertThat(result).isEqualTo(expected);
	}

	class Calculator {
		int add(int a, int b) {
			return a + b;
		}
	}
}
