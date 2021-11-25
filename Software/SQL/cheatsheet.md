
### Links

- [Formatter](https://www.dpriver.com/pp/sqlformat.htm)

### CREATE DATABASE

```sql
CREATE DATABASE <name>;

show databases;

USE <database name>;

SELECT database();

DROP DATABASE <name>;
```

### CREATE TABLE

```sql
-- not null
CREATE TABLE cats2
(
  name VARCHAR(100) NOT NULL,
  age INT NOT NULL
);

-- 預設值
CREATE TABLE cats3
(
  name VARCHAR(100) DEFAULT 'unnamed',
  age INT DEFAULT 99
);

-- primary key & AUTO_INCREMENT
CREATE TABLE unique_cats(
    cat_id INT NOT NULL AUTO_INCREMENT,
    name VARCHAR(100),
    age INT,
    PRIMARY KEY(cat_id)
);


DESC <tablename>; -- describe

SHOW TABLES;

DROP TABLE <tablename>;

```

### 建立資料

```sql
INSERT INTO table_name(column_name) VALUES (data);
INSERT INTO cats(name, age) VALUES ('Jetson', 7);
```

### READ

```sql

SELECT name FROM cats;
SELECT name, age FROM cats;

SELECT * FROM cats WHERE age=4;
SELECT * FROM cats WHERE name='Egg';

SELECT cat_id As id, name FROM cats;
SELECT name AS 'cat name', breed AS 'kitty breed' FROM cats;
```

### Update

```sql
UPDATE cats SET breed='Shorthair' WHERE breed='Tabby';
UPDATE cats SET age=14 WHERE name='Misty';
```

### Delete

```sql
DELETE FROM cats WHERE name='Egg'; 
```

### String Functions

```sql
SELECT 
  CONCAT(author_fname, ' ', author_lname) AS Author
FROM books;

SELECT SUBSTRING(title, 1, 10) AS 'short title' from books;

SELECT REPLACE(title, 'e', '3') FROM books;

SELECT REVERSE('Hello World');

SELECT CHAR_LENGTH('Hello World');
SELECT author_lname, CHAR_LENGTH(author_lname) AS 'length' FROM books;

SELECT UPPER('Hello Wrold');
SELECT LOWER('Hello Wrold');

```

### 其他

```sql
SHOW WARNINGS;
```