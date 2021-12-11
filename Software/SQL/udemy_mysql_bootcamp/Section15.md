# Section 15: Working With Lots Of Instagram Data

## create data

```sql
source Instagram/ig_clone.sql
```

## Challenges 1

- finding 5 oldest users

```sql
SELECT username, created_at 
FROM users 
ORDER BY created_at
LIMIT 5;
```

## Challenges 2

- What day of the week to most users register on?
- Most popular registration date


```sql
SELECT 
    DATE_FORMAT(created_at, '%W') AS 'day',
    COUNT(*) AS num
FROM users
GROUP BY day
ORDER BY num DESC
LIMIT 2;

-- course answer
SELECT 
    DAYNAME(created_at) AS day,
    COUNT(*) AS total
FROM users
GROUP BY day
ORDER BY total DESC
LIMIT 2;
```

## Challenges 3

- Find the users who never posted a photo(inactive users)

```sql
SELECT 
    users.id, username, image_url  
FROM users   
LEFT JOIN photos       
    ON photos.user_id = users.id 
GROUP BY users.id 
HAVING image_url IS NULL;

-- course answer
SELECT username
FROM users
LEFT JOIN photos       
    ON photos.user_id = users.id 
WHERE photos.id IS NULL;

```

## Challenges 4

-- who get the most likes on a single photo

```sql
-- course answer
SELECT 
    username,
    photos.id, 
    photos.image_url,
    COUNT(*) AS total
FROM photos
INNER JOIN likes
    ON likes.photo_id = photos.id
INNER JOIN users
    ON photos.user_id = users.id
GROUP BY photos.id
ORDER BY total DESC
LIMIT 1;
```

## Challenges 5

- how many times does the average user post?


```sql
SELECT 
    (SELECT COUNT(*) FROM photos) / (SELECT COUNT(*) FROM users);
```

## Challenges 6

- What are the most top 5 most commonly used hashtags;

```sql
SELECT 
    tags.id, 
    tag_name, 
    COUNT(*) AS total  
FROM photo_tags 
JOIN tags 
    ON tags.id = photo_tags.tag_id 
GROUP BY tags.id 
ORDER BY total DESC 
LIMIT 5;

```

## Challenges 7

- Find users who have liked every single photo on the site

```sql
SELECT 
    username, user_id,
    COUNT(*) AS num_likes
FROM users
INNER JOIN likes
    ON users.id = likes.user_id
GROUP BY users.id
HAVING num_likes = 
    (SELECT COUNT(*) FROM photos);
```
