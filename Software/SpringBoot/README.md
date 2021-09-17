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

