# Section 13: Many To Many

## Basics

- examples
  - books <-> authors
  - blog posts <-> tags
  - students <-> classes
  - tv shows <-> reviews

- Data 
  1. Series
  2. Reviews 
  3. Reviewers


## Create tables

```sql
CREATE DATABASE tv_review_app;

CREATE TABLE reviewers(
    id INT AUTO_INCREMENT PRIMARY KEY,
    first_name VARCHAR(100),
    last_name VARCHAR(100)
);

CREATE TABLE series(
    id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(100),
    released_year YEAR(4),
    genre VARCHAR(100)
);


CREATE TABLE reviews(
    id INT AUTO_INCREMENT PRIMARY KEY,
    rating DECIMAL(2,1),
    reviewer_id INT,
    series_id INT,
    FOREIGN KEY(series_id) REFERENCES series(id),
    FOREIGN KEY(reviewer_id) REFERENCES reviewers(id)
);

-- and then insert data

```

## Challenge 1


```sql

-- Challenge 1 show title and each review's rating
SELECT title, rating 
FROM series 
JOIN reviews 
  ON series.id = reviews.series_id
ORDER BY title;
```

## Challenge 2


```sql

-- Challenge 2: show title and their average rating 
SELECT title, AVG(rating) AS avg_rating
FROM series
JOIN reviews
  ON series.id = reviews.series_id
GROUP BY series.id
ORDER BY avg_rating;

```

## Challenge 3


```sql
-- Challenges 3: first_name, last_name, rating
SELECT first_name, last_name, rating 
FROM reviews
JOIN reviewers 
    ON reviews.reviewer_id = reviewers.id

-- same in this cases
SELECT first_name, last_name, rating
FROM reviewers
JOIN reviews
    ON reviews.reviewer_id = reviewers.id;

```

## Challenge 4


```sql

-- Challenges 4: show unreviewed series
SELECT 
    title AS 'unreviewed series', 
    COUNT(rating) 
FROM series 
LEFT JOIN reviews 
    ON reviews.series_id = series.id  
GROUP BY series.id
HAVING COUNT(rating) = 0;

-- WHERE COUNT(rating) = 0
-- You cannot use the WHERE clause when you use a GROUP BY clause. You would need to use HAVING:

-- course answer
SELECT title AS unreviewed_series
FROM series
LEFT JOIN reviews
    ON series.id = reviews.series_id
WHERE rating IS NULL;

```

## Challenge 5

```sql

-- Challenges 5: show genre and their average rating
SELECT genre, ROUND(AVG(rating),2)  AS avg_rating 
FROM series 
JOIN reviews 
    ON reviews.series_id = series.id  
GROUP BY genre;

-- ROUND function 
-- ROUND(AVG(rating), 2)
```


## Challenge 6

```sql
-- Challenges 6: show the stats of reviewers

SELECT 
    first_name, 
    last_name, 
    CASE  
        WHEN rating IS NULL THEN 0
        ELSE COUNT(rating) 
    END AS 'COUNT',
    IFNULL(MIN(rating), 0.0) AS 'MIN',
    IFNULL(MAX(rating), 0.0) AS 'MAX',
    IFNULL(AVG(rating), 0.0) AS 'AVG',
    CASE 
        WHEN rating IS NULL THEN 'INACTIVE'
        ELSE 'ACTIVE' 
    END AS 'STATUS'
FROM reviewers 
LEFT JOIN reviews 
    ON reviewers.id = reviews.reviewer_id
GROUP BY reviewers.id;

-- COURSE ANSWER:

-- COUNT(rating) AS COUNT

-- CASE
--     WHEN COUNT(rating) >= 1 THEN 'ACTIVE'
--     ELSE 'INACTIVE'
-- END AS STATUS

-- same as below
-- IF(COUNT(rating) >= 1, 'ACTIVE', 'INACTIVE') AS STATUS

```

## Challenge 7

```sql
-- Challenge 7: title, rating, reviewer
SELECT title, rating, 
    CONCAT(first_name, ' ', last_name) AS reviewer 
FROM reviews 
JOIN reviewers 
    ON reviewers.id = reviews.reviewer_id 
JOIN series 
    ON series.id = reviews.series_id 
ORDER BY title;

```
