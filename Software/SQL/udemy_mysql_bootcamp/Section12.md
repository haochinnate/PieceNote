# Section 12: One To Many

## relationships and JOINS

### types of data relationships

1. One to One
2. One to Many
  - A book to many reviews
  - review belong to one book
3. Many to Many 
  - books and authors

## One To Many and Foreign Keys

- primary key, always unique in a table
- foreign key, reference to other table

```sql

-- customer_id, first_name, last_name, email
CREATE TABLE customers(
    id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(100),
    last_name VARCHAR(100),
    email VARCHAR(100)
);

-- order_id, order_date, amount, customer_id
CREATE TABLE orders(
    id INT PRIMARY KEY AUTO_INCREMENT,
    order_date DATE,
    amount DECIMAL(8,2)
    customer_id INT,
    FOREIGN KEY(customer_id) REFERENCES customers(id)
);

-- customer_id cannot find customer, will have error
INSERT INTO orders(order_date, amount, customer_id) 
VALUES('2016/06/06', 33.67, 98);

```

## Cross Join

```sql
-- nested query
SELECT * FROM orders 
WHERE customer_id = ( 
    SELECT id FROM customers WHERE last_name='George'
); 

-- 5*5, every customer combine every order 
-- not useful
SELECT * FROM customers, orders;

```

## INNER JOIN

```sql
-- IMPLICIT INNER JOIN (cross join with constraint)
SELECT * FROM customers, orders 
WHERE customer.id = orders.customer_id;


-- EXPLICIT INNER JOIN (better approach)
SELECT first_name, last_name, order_date, amount FROM customers 
JOIN orders
    ON customer.id = orders.customer_id;
```

## LEFT JOIN

```sql

SELECT first_name, last_name, order_date, amount 
FROM customers
JOIN orders 
    ON customers.id = orders.customer_id
ORDER BY amount;

SELECT first_name, last_name, order_date, amount
FROM customers
JOIN orders
    ON customers.id = orders.customer_id
GROUP BY orders.customer_id

SELECT 
    first_name, 
    last_name, 
    SUM(amount) AS total_spent
FROM customers
JOIN orders
    ON customers.id = orders.customer_id
GROUP BY orders.customer_id
ORDER BY total_spent DESC;

-- LEFT JOIN
SELECT * FROM customers
LEFT JOIN orders
    ON customers.id = orders.customer_id;

SELECT 
    first_name, 
    last_name, 
    IFNULL(SUM(amount), 0) AS total_spent
FROM customers
LEFT JOIN orders
    ON customers.id = orders.customer_id
GROUP BY customers.id
ORDER BY total_spent;

```

## RIGHT JOIN

```sql
SELECT first_name, last_name, order_date, amount 
FROM customers
RIGHT JOIN orders
    ON customers.id = orders.customer_id;


SELECT 
    IFNULL(first_name, 'MISSING') AS first, 
    IFNULL(last_name, 'USER') AS last, 
    order_date, 
    amount,
    SUM(amount)
FROM customers
RIGHT JOIN orders
    ON customers.id = orders.customer_id
GROUP BY customer_id;


-- ON DELETE CASCADE
CREATE TABLE orders(
  id INT AUTO_INCREMENT PRIMARY KEY,
  order_date DATE,
  amount DECIMAL(8,2),
  customer_id INT,
  FOREIGN KEY(customer_id) 
      REFERENCES customer(id) 
      ON DELETE CASCADE
);

-- CASCADE: delete customers will also delete orders
DELETE FROM customers WHERE email = 'george@gmail.com';
```

## Exercises

```sql
CREATE TABLE students(
    id INT AUTO_INCREMENT PRIMARY KEY,
    first_name VARCHAR(100)
);

CREATE TABLE papers(
    id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(100)
    grade INT,
    student_id INT,
    FOREIGN KEY(student_id) 
        REFERENCES students(id)
        ON DELETE CASCADE
);

-- EXERCISE 1
SELECT first_name, title, grade 
FROM papers
JOIN students 
    ON papers.student_id = students.id
ORDER BY grade DESC;

-- EXERCISE 2
SELECT first_name, title, grade
FROM students
LEFT JOIN papers
    ON papers.student_id = students.id;

-- EXERCISE 3
SELECT 
    first_name, 
    IFNULL(title, 'MISSING'), 
    IFNULL(grade, 0)
FROM students
LEFT JOIN papers
    ON papers.student_id = students.id;

-- EXERCISE 4
SELECT 
    first_name,
    IFNULL(AVG(grade), 0) AS 'average'
FROM students
LEFT JOIN papers
    ON papers.student_id = students.id
GROUP BY students.id
ORDER BY 'average' DESC;

-- EXERCISE 5
SELECT 
    first_name,
    IFNULL(AVG(grade), 0) AS average,
    CASE 
        WHEN AVG(grade) IS NULL THEN 'FAILING'
        WHEN AVG(grade) >= 75 THEN 'PASSING'
        ELSE 'FAILING'
    END AS passing_status
FROM students
LEFT JOIN papers
    ON papers.student_id = students.id
GROUP BY students.id
ORDER BY average DESC;

-- WHE AS 'average' didn't ORDER as expected?
-- BUT AS average can sort successfullt?
```

