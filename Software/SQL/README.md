
# Section 2: Getting Started

- SQL is the language we use to "talk" to our databases

## goormIDE

- 原本用 cloud9, 現在改用[goormIDE](https://ide.goorm.io/)

- [Goorm MySQL Cheat Sheet](https://gist.github.com/nax3t/767e06f6af0bafc70b4c4cba0c8d38e7)

- [建立步驟](https://gist.github.com/nax3t/2773378c4d1bada8d66d12f4d5210248)

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
