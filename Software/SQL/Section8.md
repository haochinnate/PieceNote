# Section 8: Refining Our Selections

## DISTINCT

```sql
SELECT DISTINCT author_lname FROM books;

SELECT DISTINCT CONCAT(author_fname, ' ', author_lname) FROM books;

-- simple way distinct with full name
SELECT DISTINCT author_fname, author_lname FROM books;

```

## ORDER BY

```sql
-- 預設順序是遞增
SELECT author_lname FROM books ORDER BY author_lname;

-- descending
SELECT author_lname FROM books ORDER BY author_lname DESC;

-- 2 = author_fname
SELECT title, author_fname, author_lname FROM books ORDER BY 2;

-- order by multiple column
SELECT author_fname, author_lname FROM books ORDER BY author_lname, author_fname;
```

## LIMIT

```sql

SELECT title FROM books LIMIT 3;

SELECT title, released_year FROM books ORDER BY released_year DESC LIMIT 5;

-- argument: 'starting point', 'rows count' 
SELECT title, released_year FROM books ORDER BY released_year DESC LIMIT 0,5;

-- some big number to get all rows
SELECT * FROM tbl LIMIT 95, 18446744073709551615;
```

## LIKE

- %: for wildcards

```sql
SELECT title FROM books WHERE author_fname LIKE '%da%';

-- start with 'da'
SELECT title FROM books WHERE author_fname LIKE 'da%';

```

- _: 剛好一個字元

```sql
SELECT title, stock_quantity FROM books WHERE stock_quantity LIKE '____';
```

- 如果搜尋對象裡面有 %, _, 使用 escape character \

```sql

SELECT title FROM books WHERE title LIKE '%\%%';
-- or '%\_%'
```

## Challenges 

```sql

-- titles that contain 'stories' 
SELECT title FROM books WHERE title LIKE '%stories%';

-- longest book
SELECT title, pages FROM books ORDER BY pages DESC LIMIT 1;

-- prinit out summary containing the title, year
SELECT 
    CONCAT(title, ' - ', released_year) AS 'summary' 
FROM books 
ORDER BY released_year DESC LIMIT 3;

-- find all books with author last name that contains a space
SELECT title, author_lname FROM books WHERE author_lname LIKE '% %';

-- find the 3 books with the lowest stock
SELECT title, released_year, stock_quantity 
FROM books 
ORDER BY stock_quantity LIMIT 3;

-- sorted by author_lname and then by title
SELECT title, author_lname 
FROM books
ORDER BY author_lname, title;

-- sort by last name
SELECT 
    UPPER(
        CONCAT(
            'My favorite author is', 
            author_fname, 
            ' ', 
            author_lname, 
            '!'
        )
    )
AS 'yell'
FROM books
ORDER BY author_lname;

```
