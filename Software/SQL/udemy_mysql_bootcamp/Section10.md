# Section 10: Revisiting Data Types

## Storing Text

### CHAR

- CHAR has a __fixed length__
- CHAR is faster for fixed length text

```sql

-- CHAR(3)
-- only 3 characters, right-padded with spaces to specified length

CREATE TABLE dogs(name CHAR(5), breed VARCHAR(10));
INSERT INTO dogs (name, breed) VALUES('bob', 'beagle');
INSERT INTO dogs (name, breed) VALUES('Princess Jane', 'Retriever');
SELECT * FROM dogs;

```

## DECIMAL

```sql
-- DECIMAL(13, 2)
-- 13: Total number of Digits
-- 2: Digits after decimal
CREATE TABLE items(price DECIMAL(5,2));
INSERT INTO items (price) VALUES(7);
INSERT INTO items (price) VALUES(299999); -- save as 999.99

INSERT INTO items(price) VALUES(34.88);
INSERT INTO items(price) VALUES(289.9999); -- save as 290.00

INSERT INTO items(price) VALUES(1.9999); -- save as 2.00

```

## FLOAT and DOUBLE

```sql
CREATE TABLE thingies(price FLOAT);
INSERT INTO thingies(price) VALUE (88.45);
INSERT INTO thingies(price) VALUE (8877.45);
INSERT INTO thingies(price) VALUE (8877665544.45);
```

## DATE, TIME, DATETIME

```sql

CREATE TABLE people(
    name VARCHAR(100),
    birthdate DATE,
    birthtime TIME,
    birthdt DATETIME
);

INSERT INTO people(name, birthdate, birthtime, birthdt) VALUE ('Padma', '1983-11-11', '10:07:35','1983-11-11 10:07:35');

INSERT INTO people(name, birthdate, birthtime, birthdt) VALUE ('Larry', '1943-12-25', '04:10:42','1943-12-25 04:10:42');

SELECT * FROM people;


```

## CURDATE, CURTIME, NOW

```sql
CURDATE() -- current date
CURTIME() -- current time 
NOW() -- current datetime

SELECT CURDATE();
SELECT NOE();

INSERT INTO people(name, birthdate, birthtime, birthdt) VALUES('Microwave', CURDATE(), CURTIME(), NOW());
```

## Formatting DATES

```sql
SELECT name, DAY(birthdate) FROM people;
-- DAYNAME(birthdate) Monday...etc..
-- DAYOFWEEK, number
-- DAYOFYEAR
-- MONTH
-- MONTHNAME
-- 上面這些對 time 使用的話, 會得到 NULL 和 warning

MINUTE(birthtime)


SELECT DATE_FORMAT(birthdt, '%W %M %Y') FROM people;
SELECT DATE_FORMAT(birthdt, '%W') FROM people;
SELECT DATE_FORMAT(birthdt, '%m/%d/%Y') FROM people;
SELECT DATE_FORMAT(birthdt, '%m/%d/%Y at %h:%i') FROM people;

```


