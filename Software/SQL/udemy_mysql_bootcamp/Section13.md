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

-- Challenge 1 show title and each review's rating
SELECT title, rating 
FROM series 
JOIN reviews 
  ON series.id = reviews.series_id
ORDER BY title;


-- Challenge 2: show title and their average rating 
SELECT title, AVG(rating) AS avg_rating
FROM series
JOIN reviews
  ON series.id = reviews.series_id
GROUP BY series.id
ORDER BY avg_rating;

```