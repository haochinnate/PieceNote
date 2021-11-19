# Section 3: Creating Databases and Tables

```sh
# 進入 mysql
mysql-ctl cli

# 離開
\q
```

## 建立資料庫

```sql
-- 列出MySQL中存在的 database
show databases;

-- 建立 database
CREATE DATABASE <name>;
CREATE DATABASE soap_store;
```

## 刪除資料庫

```sql
-- 刪除 database
DROP DATABASE <name>;
DROP DATABASE hello_world_db;
```

## Use database

```sql
USE <database name>;
USE dog_walking_app;

-- 得知目前使用的 database
SELECT database();
-- 如果DROP database 再執行, 則使用中的 database 會是NULL
```

## Table 簡介

- A database is just a bunch of __tables__

- data types focus on: INT, VARCHAR

- 範例: Tweets Table
  - username: VARCHAR(15)
  - content: VARCHAR(140)
  - favoritesNumber: INT

## 建立 table

```sql
CREATE TABLE tablename(
    column_name data_type,
    column_name data_type,
);

CREATE DATABASE cat_app;
USE cat_app;
 SELECT database();

CREATE TABLE cats(
    name VARCHAR(100),
    age INT
);

```

## 刪除 table

```sql
-- 看是否有建立成功
SHOW TABLES;
SHOW COLUMNS FROM <tablename>;
SHOW COLUMNS FROM cats
DESC <tablename>; -- describe

-- 刪除 table
DROP TABLE <tablename>;
DROP TABLE cats;

```


