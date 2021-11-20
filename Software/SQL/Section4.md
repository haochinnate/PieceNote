# Section 4: Inserting data 

## Inserting Data

```sql
-- ORDER DOES MATTER!
INSERT INTO table_name(column_name) VALUES (data);
INSERT INTO cats(name, age) VALUES ('Jetson', 7);

SELECT * FROM cats;
```

## Multiple Insert

```sql

INSERT INTO cats(name, age) 
VALUES ('Charlie', 10),
       ('Sadie', 3),
       ('Lazy Bear',1);
```

- 輸入資料含引號
  - Escape the quotes with a backslash: "This text has \"quotes\" in it" or 'This text has \'quotes\' in it'
  - Alternate single and double quotes: "This text has 'quotes' in it" or 'This text has "quotes" in it'

## Warning

- 輸入太長的 name 時, 會有 warning
- age 輸入字串也會有 warning

```sql
-- 觀看警告, 要在下完指令之後就看, 
-- 如果中間有其他指令成功執行, warning set 就會清空
SHOW WARNINGS;
```

## NULL

- the value is not known

```sql
-- 目前可以只insert name, age的值那欄是 null
INSERT INTO cats(name) VALUES('Alabama');
INSERT INTO cats() VALUES();
```

- 宣告時設定 not null

```sql
CREATE TABLE cats2
(
  name VARCHAR(100) NOT NULL,
  age INT NOT NULL
);

-- 這個會有 warning, 說 age 沒有預設值, age 值會是0
INSERT INTO cats2(name) VALUES('name');
-- name 值是空字串
INSERT INTO cats2(age) VALUES(7);
```

## 預設值

```sql
CREATE TABLE cats3
(
  name VARCHAR(100) DEFAULT 'unnamed',
  age INT DEFAULT 99
);

-- 這行還是可以的, 因為 cats3 沒有限制 NOT NULL
INSERT INTO cats3(name, age) VALUES('Montana', NULL);

```

## Primary Key

- A Unique Identifier

```sql
CREATE TABLE unique_cats(
    cat_id INT NOT NULL,
    name VARCHAR(100),
    age INT,
    PRIMARY KEY(cat_id)
);

-- 這會自己指定 cat_id 為 0
INSERT INTO unique_cats(name, age) VALUES ('name', 3);

-- 自動增加: AUTO_INCREMENT
CREATE TABLE unique_cats2(
  cat_id INT NOT NULL AUTO_INCREMENT,
  name VARCHAR(100),
  age INT,
  PRIMARY KEY(cat_id)
); 

-- 如果 INSERT INTO 指定了 cat_id, 下一個沒指定的, 會從最大的ID往後加?
```

## 練習

```sql
CREATE TABLE employees(
  id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
  last_name VARCHAR(100) NOT NULL,
  first_name VARCHAR(100) NOT NULL, 
  middle_name VARCHAR(100),
  age INT NOT NULL,
  current_status VARCHAR(100) NOT NULL DEFAULT 'employed',
);
```

