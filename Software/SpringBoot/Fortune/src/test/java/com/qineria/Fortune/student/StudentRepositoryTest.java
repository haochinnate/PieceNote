package com.qineria.Fortune.student;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;

import java.time.LocalDate;
import java.time.Month;
import java.util.Optional;

import static org.assertj.core.api.AssertionsForClassTypes.assertThat;

@DataJpaTest
class StudentRepositoryTest {

    @Autowired
    private StudentRepository underTest;

    @BeforeEach
    void setUp() {

    }

    @AfterEach
    void tearDown() {
        underTest.deleteAll();
    }

    @Test
    void itShouldFindStudentByEmail() {
        // given
        String email = "jamila@gmail.com";
        Student student = new Student(
                "Jamila", email,
                LocalDate.of(2004, Month.JANUARY, 5)
        );
        underTest.save(student);

        // when
        Optional<Student> expected = underTest.findStudentByEmail(email);

        // then
        assertThat(expected).isNotNull();
    }

    @Test
    void itShouldFindStudentByEmailFailedCase() {
        // given
        String email = "jamila@gmail.com";

        // when
        Optional<Student> expected = underTest.findStudentByEmail(email);

        // then
        assertThat(expected).isEqualTo(Optional.empty());
    }
}