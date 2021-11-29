# Section 9: The Magic of Aggregate Functions

## COUNT

```sql
-- count every row
SELECT COUNT(*) FROM books;

-- how many author_fname
SELECT COUNT(author_fname) FROM books;
SELECT COUNT(DISTINCT author_fname) FROM books;

-- number unique author
SELECT COUNT(DISTINCT author_fname, author_lname) FROM books;

-- how many titles contain "the"
SELECT COUNT(*) FROM books WHERE title LIKE '%the%';

```

## GROUP BY

```sql

SELECT author_lname, COUNT(*) FROM books GROUP BY author_lname;

SELECT author_fname, author_lname, COUNT(*) FROM books GROUP BY author_lname, author_fname;

-- CONCAT('In ', released_year, ' ',  COUNT(*), ' book(s) released')
SELECT released_year, COUNT(*) FROM books GROUP BY released_year; 

```

## MIN and MAX

```sql

SELECT MIN(released_year) FROM books; 

SELECT MAX(CHAR_LENGTH(title)) FROM books;

-- not as you think...
SELECT MAX(pages), title FROM books;

-- use solutions in SUBQUEIRES
```

## SUBQUEIRES

```sql

SELECT title, pages FROM books WHERE pages = (SELECT MAX(pages) FROM books);

SELECT title, pages FROM books ORDER BY pages ASC LIMIT 1;

```

## MIN/MAX with GROUP BY

```sql

-- find the year each author published their first book
SELECT author_fname, author_lname, MIN(released_year)
FROM books
GROUP BY author_lname, author_fname;

-- find the longest page count for each author
SELECT author_fname, author_lname, MAX(pages)
FROM books
GROUP BY author_lname, author_fname;

```

## SUM

```sql
SELECT SUM(pages) FROM books;

SELECT author_fname, author_lname, SUM(pages) 
FROM books 
GROUP BY author_fname, author_lname;

```

## AVG

```sql
SELECT AVG(released_year) FROM books;

-- calculate the average stock quantity for books released in the same year
SELECT released_year, AVG(stock_quantity) 
FROM books 
GROUP BY released_year;

SELECT author_fname, author_lname, AVG(pages) 
FROM books
GROUP BY author_fname, author_lname;

```

## Challenges 

```sql

-- print the number of books in the database
SELECT COUNT(*) FROM books;

-- print out how many books were released in each year
SELECT released_year, COUNT(*) FROM books GROUP BY released_year;

-- print out the total number of books in stock
SELECT SUM(stock_quantity) FROM books;

-- find the average released year for each author
SELECT author_fname, author_lname, AVG(released_year) 
FROM books
GROUP BY author_fname, author_lname;

-- find the full name of the author who wrote the longest book
SELECT CONCAT(author_fname, ' ', author_lname) AS 'full name', pages 
FROM books 
ORDER BY pages DESC 
LIMIT 1;

-- list average pages, books number of each year
SELECT 
    released_year as 'year', 
    COUNT(*) as '# books',
    AVG(pages) as 'avg pages'
FROM books
GROUP BY released_year;

```
