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

