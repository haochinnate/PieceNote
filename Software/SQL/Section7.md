# Section 7: The World Of String Functions

## Running SQL Files

```sh
ls

# create query.sql

mysql-ctl cli
```

```sql
-- run the script in file
source query.sql
source testing/insert.sql

CREATE DATABASE book_shop;
```

## CONCAT

```sql
SELECT author_fname, author_lname FROM books;

-- CONCAT
SELECT 
  CONCAT(author_fname, ' ', author_lname) AS Author
FROM books;

-- CONCAT_WS (concat with separator)
SELECT 
  CONCAT_WS(' - ', title, author_fname, author_lname)
FROM books;
```

## SUBSTRING

```sql
-- index start from 1 !!!!!
SELECT SUBSTRING('Hello World', 1, 4);

SELECT title FROM books;

SELECT SUBSTRING(title, 1, 10) AS 'short title' from books;

-- SUBSTR() 也可以

-- 與 CONCAT 結合
SELECT CONCAT
    (
        SUBSTRING(title, 1, 10), 
        '...'
    ) 
    AS 'short title'
FROM books;
```

## REPLACE

```sql
SELECT REPLACE('Hello World', 'Hell', '%$#@');
SELECT REPLACE(title, 'e', '3') FROM books;
```

## REVERSE

```sql
SELECT REVERSE('Hello World');
```

## CHAR_LENGTH

```sql

SELECT CHAR_LENGTH('Hello World');
SELECT CONCAT(
    author_lname, ' is ', CHAR_LENGTH(author_lname), ' characters long'
) 
FROM books;

```

## UPPER and LOWER

```sql

SELECT UPPER('Hello Wrold');
SELECT LOWER('Hello Wrold');

```

## Challenges 

```sql

SELECT 
UPPER(
    REVERSE('Why does my cat look at me with such hatred?')
);

SELECT REPLACE(title, ' ', '->') AS 'title' FROM books;

SELECT author_lname AS 'forwards', REVERSE(author_lname) AS 'backwards' FROM books;

SELECT UPPER(
    CONCAT(author_fname, ' ', author_lname)
) AS 'full name in caps'
FROM books;

SELECT 
    CONCAT(title, ' was released in ', released_year )
    AS 'blurb' 
FROM books;

SELECT 
    title, 
    CHAR_LENGTH(title) AS 'character count' 
FROM books;

SELECT 
    CONCAT(SUBSTRING(title, 1, 10), '...') AS 'short title',
    CONCAT(author_lname, ',', author_fname) AS 'author',
    CONCAT(stock_quantity, ' in stock') AS 'quantity'
FROM books;

```