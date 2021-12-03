# Section 11: The Power of Logical Operators

## NOT EQUAL

```sql
-- !=
SELECT title, released_year FROM books WHERE released_year!=2017; 

SELECT title, author_lname FROM books WHERE author_lname != 'Harris';
```

## NOT LIKE

```sql
-- select books with title that don't start with 'W'
SELECT title FROM books WHERE title NOT LIKE 'W%';
```

## GREATER THAN

```sql
-- > 

SELECT title, released_year FROM books WHERE released_year > 2000 ORDER BY released_year;

-- >=
SELECT title, stock_quantity FROM books WHERE stock_quantity >=100;

SELECT 99 > 1;
-- the result is 1
SELECT 99 < 1; -- the result is 0

SELECT 'a' > 'b'; -- 0
SELECT 'a' < 'b'; -- 1

SELECT 'A' > 'a'; -- 0
SELECT 'A' < 'a'; -- 0
SELECT 'A' = 'a'; -- 1
```

## LESS THAN

```sql
SELECT title, released_year FROM books WHERE released_year < 2000 ORDER BY released_year;

SELECT 3 < -10; -- 0
SELECT -10 < -9; -- 1
SELECT 42 <= 42; -- 1
SELECT 'h' < 'p'; -- 1
SELECT 'H' > 'p'; -- 0
SELECT 'Q' <= 'q'; -- 1

```

## Logical AND

```sql
-- select books written by Dave Eggers, published after the year 2010
SELECT title, author_lname, released_year FROM books 
WHERE author_lname = 'Eggers' 
AND released_year > 2010;

SELECT -10 > -20 && 0 <= 0; -- 1
SELECT -40 <= 0 AND 10 > 40; -- 0
SELECT 54 <= -54 AND 'a' = 'A'; -- 1 

SELECT title, author_lname, released_year FROM books 
WHERE author_lname = 'Eggers' 
AND released_year > 2010;
AND title LIKE '%novel%';
```

## Logical OR

```sql

SELECT 40 <= 100 || -2 > 0; -- 1
SELECT 10 > 5 || 5 = 5; -- 1
SELECT 'a' = 5 || 3000 > 2000; -- 1

SELECT title, author_lname, released_year, stock_quantity FROM books 
WHERE author_lname = 'Eggers' 
OR released_year > 2010
OR stock_quantity > 100;

```

## BETWEEN

```sql

-- use >, <, AND to implement BETWEEN
-- select all books published between 2004 and 2015
SELECT title, released_year FROM books 
WHERE released_year >= 2004 
AND released_year <= 2015;

-- use BETWEEN
SELECT title, released_year FROM books 
WHERE released_year BETWEEN 2004 AND 2015;

-- NOT BETWEEN
SELECT title, released_year FROM books 
WHERE released_year NOT BETWEEN 2004 AND 2015;

-- cast, use with DATE, TIME, DATETIME
SELECT CAST('2017-05-02' AS DATETIME); -- 2017-05-02 00:00:00

SELECT name, birthdt FROM people 
WHERE birthdt BETWEEN '1980-01-01' AND '2000-01-01';

SELECT name, birthdt FROM people 
WHERE birthdt BETWEEN CAST('1980-01-01' AS DATETIME) AND CAST('2000-01-01' AS DATETIME);

```

## IN, NOT IN

```sql

-- select all books written by 'Carver' or 'Lahiri' or 'Smith'
-- use OR
SELECt title, author_lname FROM books 
WHERE author_lname='Carver' OR author_lname='Lahiri' OR author_lname='Smith';

-- use IN
SELECt title, author_lname FROM books 
WHERE author_lname IN ('Carver', 'Lahiri', 'Smith');

SELECT title, released_year FROM books
WHERE released_year IN (2017, 1985);

SELECT title, released_year FROM books WHERE released_year >= 2000 AND released_year % 2 != 0;
```

## CASE STATEMENTS

```sql

-- CASE...END
SELECT title, released_year,
    CASE
        WHEN released_year >= 2000 THEN 'Modern Lit'
        ELSE '20th Century Lit'
    END AS GENRE
FROM books;

SELECT title, stock_quantity, 
    CASE 
        WHEN stock_quantity BETWEEN 0 AND 50 THEN '*'
        WHEN stock_quantity BETWEEN 51 AND 100 THEN '**'
        ELSE '***'
    END AS STOCK
FROM books;    

-- as below
SELECT title, stock_quantity,
    CASE
        WHEN stock_quantity <= 50 THEN '*'
        WHEN stock_quantity <= 100 THEN '**'
        ELSE '***'
    END AS STOCK
FROM books;

```

## Exercises

```sql

SELECT 10 != 10; -- 0
SELECT 15 > 14 && 99 - 5 <= 94; -- 1
SELECT 1 IN (5,3) || 9 BETWEEN 8 AND 10; -- 1

-- select all books writtern before 1980
SELECT title, released_year FROM books
WHERE released_year < 1980;

-- select all books written by Eggers or Chabon
SELECT title, author_lname FROM books 
WHERE author_lname IN ('Eggers', 'Chabon');
-- WHERE author_lname = 'Eggers' OR author_lname = 'Chabon';

-- select all books written by 'Lahiri' published after 2000
SELECT title, author_lname, released_year FROM books 
WHERE author_lname = 'Lahiri' AND released_year > 2000;

-- select all books with page counts between 100 and 200
SELECT title, pages FROM books 
WHERE pages BETWEEN 100 AND 200;

-- select all books where author_lname starts with a 'C' or 'S'
SELECT title, author_lname FROM books 
WHERE author_lname LIKE 'C%' OR author_lname LIKE 'S%';
-- SUBSTR(author_lname, 1, 1) = 'C' OR SUBSTR(author_lname, 1, 1) = 'S'
-- SUBSTR(author_lname, 1, 1) IN ('C', 'S') 

SELECT title, author_lname, 
    CASE
        WHEN title LIKE '%stories%' THEN 'Short Stories'
        WHEN title = 'Just Kids' OR title LIKE 'A Heartbreaking Work%' THEN 'Memoir'
        ELSE 'Novel'
    END AS 'TYPE'
FROM books;


SELECT title, author_fname, author_lname, 
    CASE 
        WHEN COUNT(title) = 1 THEN '1 book'
        ELSE CONCAT(COUNT(title), ' books')
    END AS 'COUNT'
FROM books 
GROUP BY author_lname, author_fname;

```

