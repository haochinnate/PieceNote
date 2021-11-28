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