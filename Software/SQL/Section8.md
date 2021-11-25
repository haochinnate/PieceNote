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

```
