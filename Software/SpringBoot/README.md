- [Spring Start](https://start.spring.io/)

- https://start.spring.io/#!type=gradle-project&language=java&platformVersion=2.5.4&packaging=jar&jvmVersion=11&groupId=com.qineria&artifactId=Fortune&name=Fortune&description=Demo%20project%20for%20Spring%20Boot&packageName=com.qineria.Fortune&dependencies=lombok,web,data-jpa,postgresql

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
    public void deleteStudent(Long studentId) {
        boolean exists = studentRepository.existsById(studentId);
        if (!exists) {
            throw new IllegalStateException(
                    "student with id " + studentId + " does not exists");
        }
        studentRepository.deleteById(studentId);
    }
```