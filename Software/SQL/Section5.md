# Section 5: CRUD commands

## preparing data

```sql
-- delete table
DROP TABLE cats;

-- create new table
CREATE TABLE cats(
    cat_id INT NOT NULL AUTO_INCREMENT,
    name VARCHAR(100),
    breed VARCHAR(100),
    age INT,
    PRIMARY KEY(cat_id)
);

DESC cats;

-- and then insert data
```

## SELECT and WHERE

```sql
SELECT name FROM cats;
SELECT name, age FROM cats;
-- order is matter
```

- WHERE, get specifical

```sql
SELECT * FROM cats WHERE age=4;
SELECT * FROM cats WHERE name='Egg';
SELECT * FROM cats WHERE name='EGG'; -- still works!!

SELECT name, age FROM cats WHERE breed='Tabby';
SELECT cat_id, age FROM cats WHERE cat_id=age;
```

## Aliases

```sql
SELECT cat_id As id, name FROM cats;
SELECT name AS 'cat name', breed AS 'kitty breed' FROM cats;
```

## Update

```sql

```

