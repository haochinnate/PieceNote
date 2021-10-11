- [Spring Start](https://start.spring.io/)

- https://start.spring.io/#!type=gradle-project&language=java&platformVersion=2.5.4&packaging=jar&jvmVersion=11&groupId=com.qineria&artifactId=Fortune&name=Fortune&description=Demo%20project%20for%20Spring%20Boot&packageName=com.qineria.Fortune&dependencies=lombok,web,data-jpa,postgresql

# Spring Boot Tutorial

- [Youtube 影片](https://www.youtube.com/watch?v=9SGDpanrc8U)

- \src\main\resources\application.properties 用來放 config settings

- 文字修改 package 後, 對 pom.xml 右鍵 -> Maven -> reload project 

- 簡單範例
  - http://localhost:8080

```java
@RestController
public class FortuneApplication {

	@GetMapping
	public String hello() {
		return "Hello World";
	}

    @GetMapping
	public List<String> hello() {
		return List.of("Hello World", "test2");
	}
    // 回傳會是 ["",""]
}
```

## API Layer

- 建立 Student Controller, 設定 path
```java
@RequestMapping(path="api/v1/student")
public class StudentController {
}
```

## Service Layer

- 加上 service decorator

```java
@Service
public class StudentService {
    // ...
}
```

## Dependency Injection

- controller 裡面藉由 DI 取得 service

```java
private final StudentService studentService;

@Autowired
public StudentController(StudentService studentService) {
    this.studentService = studentService;
}
```

## properties file

- Data Access Layer
- 設定 application.properties
- [EDB](https://www.enterprisedb.com/) 安裝 postgresql
- postgres - mcl

```cmd
\l 列出 database

CREATE DATABASE student;

\du 列出 role, attibutes

GRANT ALL PRIVILEGES ON DATABASE "student" TO postgres

\c student 連接到 student

\d 查看 relation

SELECT * FROM student;
```

## JPA

```java
@Entity
@Table
public class Student {
    @Id
    @SequenceGenerator(
            name = "student_sequence",
            sequenceName = "student_sequence",
            allocationSize = 1
    )
    @GeneratedValue(
            strategy = GenerationType.SEQUENCE,
            generator = "student_sequence"
    )
}
```

- 會有log

```
Hibernate: create sequence student_sequence start 1 increment 1
Hibernate: 
    
    create table student (
       id int8 not null,
        age int4,
        dob date,
        email varchar(255),
        name varchar(255),
        primary key (id)
    )
```

## Data Access Layer

```java
@Repository
public interface StudentRepository 
        extends JpaRepository<Student, Long>{
}
```

- 在 Service class 裡面使用 repository class


- 建立初始資料

```java
@Configuration
public class StudentConfig {

    @Bean
    CommandLineRunner commandLineRunner(StudentRepository repository) {
    }
}
```

## Transient

- 這個 field 不用是 database 中的 column

```java
@Transient
private Integer age;
```

## POST Mapping

```java
@PostMapping
public void registrNewStudent(@RequestBody Student student) {
    studentService.addNewStudent(student);
}
```

- 利用 IntelliJ 測試 API, 或可以用 postman

```json
// POST http://localhost:8080/api/v1/student
// Content-Type: application/json

{
  "name": "Bilal",
  "email": "bilal.ahmed@gmail.com",
  "dob": "1995-12-17"
}
```

## Business logic

- 在 repository 底下新增 function 

```java

// SELECT * FROM student WHERE email = ?
@Query("SELECT s FROM Student s WHERE s.email = ?1")
Optional<Student> findStudentByEmail(String email);

```

- 在 service 裡面使用 repository 的 function

```java

    public void addNewStudent(Student student) {
        Optional<Student> studentOptional = studentRepository
                .findStudentByEmail(student.getEmail());
        if (studentOptional.isPresent()) {
            throw new IllegalStateException("email taken");
        }
        
        studentRepository.save(student);
    }

```

- 在 application.properties 設定顯示 message
    - server.error.include-message=always


## Deleting


```java
    @DeleteMapping(path = "{studentId}")
    public void deleteStudent(
            @PathVariable("studentId") Long studentId) {
        studentService.deleteStudent(studentId);
    }
```

```java
    public void deleteStudent(Long studentId) {
        boolean exists = studentRepository.existsById(studentId);
        if (!exists) {
            throw new IllegalStateException(
                    "student with id " + studentId + " does not exists");
        }
        studentRepository.deleteById(studentId);
    }
```

## Editing

- @Transactional [介紹](https://www.baeldung.com/transaction-configuration-with-jpa-and-spring)
  - 影片是說, 表示不用實作 jpql query, 使用 entity 的 setter, getter 來設定值?
- PUT http://localhost:8080/api/v1/student/1?name=Maria

```java
    @PutMapping(path = "studentId")
    public void updateStudent(
            @PathVariable("studentId") Long studentId,
            @RequestParam(required = false) String name,
            @RequestParam(required = false) String email) {
        studentService.updateStudent(studentId, name, email);
    }
```

```java
    @Transactional
    public void updateStudent(Long studentId,
                              String name,
                              String email) {
        Student student = studentRepository.findById(studentId)
                .orElseThrow(() -> new IllegalStateException(
                        "Student with id " + studentId + " does not exists"));

        if (name != null &&
                name.length() > 0 &&
                !Objects.equals(student.getName(), name)) {
            student.setName(name);
        }

        if (email != null &&
                email.length() > 0 &&
                !Objects.equals(student.getEmail(), email)) {
            Optional<Student> studentOptional = studentRepository
                    .findStudentByEmail(email);
            if (studentOptional.isPresent()) {
                throw new IllegalStateException("email taken");
            }
            student.setEmail(email);
        }
    }
```

## Packaging

- 如果有 target 資料夾的話, 刪掉

- Maven -> Lifecycle -> clean
- Maven -> Lifecycle -> install
- 在 target 資料夾中, 會有 *.jar 檔
- 在 terminal 中執行
  - cd target 
  - java -jar xxxx.jar
  - java -jar xxxx.jar --server.port=8081



# Testing

- [Youtube 影片](https://www.youtube.com/watch?v=Geq60OVyBPg)

- 裡面有包含 AssertJ, hamcrest  junit.jupiter, mockito

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-test</artifactId>
    <scope>test</scope>
</dependency>
```

## simple unit test

```java
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
```

## Test repository

```java
 @Autowired
private StudentRepository underTest;

// 在 test method 中使用 underTest
```

## H2 Database

- [官網](https://www.h2database.com/html/main.html)

```xml
<dependency>
    <groupId>com.h2database</groupId>
    <artifactId>h2</artifactId>
    <scope>test</scope>
</dependency>
```

- 在 application.properties 中做設定

```properties
spring.datasource.url=jdbc:h2://mem:db;DB_CLOSE_DELAY=-1
spring.datasource.username=sa
spring.datasource.password=sa
spring.datasource.driver-class-name=org.h2.Driver
spring.jpa.hibernate.ddl-auto=create-drop
spring.jpa.show-sql=true
```

- 在 StudentRepositoryTest 中使用, 增加 DataJpaTest

```java
@DataJpaTest
class StudentRepositoryTest {

}
```

## Mockito

- StudentServiceTest.java

- 設定

```java

@Mock
private StudentRepository studentRepository;
private AutoCloseable autoCloseable;
private StudentService underTest;

@BeforeEach
void setUp() {
    autoCloseable = MockitoAnnotations.openMocks(this);
    underTest = new StudentService(studentRepository);
}

@AfterEach
void tearDown() throws Exception {
    autoCloseable.close();
}
```

```java
@Test
void canGetAllStudents() {
    // when
    underTest.getStudents();
    // then
    // 預期有哪個 interaction, mock 有invoked findAll
    // StudentRepository 本身已經測試好了 
    verify(studentRepository).findAll();
}
```

- 如果不用 AutoCloseable, 可加 ExtendWith annotation

```java
@ExtendWith(MockitoExtension.class)
class StudentServiceTest {

}
```

## Argument Captor

```java
// 檢驗 studentRepository 有沒有呼叫 save, 並用 capture 抓取傳入 save 的參數
// 傳入 studentRepository.save 的參數, 跟傳入 service.addNewStudent 的參數一樣

// then
ArgumentCaptor<Student> studentArgumentCaptor =
        ArgumentCaptor.forClass(Student.class);
verify(studentRepository).save(studentArgumentCaptor.capture());

Student capturedStudent = studentArgumentCaptor.getValue();
assertThat(capturedStudent).isEqualTo(student);
```

## assert throw exception

```java

// 強迫設定回傳 造成 exception
given(studentRepository.findStudentByEmail(student.getEmail()))
    .willReturn(Optional.of(student));
// 其實不一定要用 email 可以是任何 string, 因為已經固定回傳值
given(studentRepository.findStudentByEmail(anyString()))
    .willReturn(Optional.of(student));


// when
assertThatThrownBy(() -> underTest.addNewStudent(student))
    .isInstanceOf(IllegalStateException.class)
    .hasMessageContaining("email taken");

// 並確認 save function 沒有被呼叫
verify(studentRepository, never()).save(any());

```

## Integration Testing Overview

```java



```