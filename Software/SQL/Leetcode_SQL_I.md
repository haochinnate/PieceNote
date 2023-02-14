# Day 1: Select

## 595. Big Countries

```sql
SELECT name, population, area FROM World 
WHERE area >= 3000000 OR population  >= 25000000;
```

## 1757. Recyclable and Low Fat Products

```sql
SELECT product_id FROM products 
WHERE low_fats = 'Y' AND recyclable = 'Y'
```

# 584. Find Customer Referee

```sql
SELECT name FROM Customer
WHERE referee_id != 2 OR referee_id IS NULL;
```

# 183. Customers Who Never Order

```sql
SELECT c.Name AS "Customers" from Customers c
WHERE c.Id NOT IN (SELECT o.CustomerId from Orders o)
```

# Day 2: Select and Order

# Day 3: String Processing Functions

# Day 3: String Processing Functions

# Day 4: Union and Select

## 1965. Employees With Missing Information

- Two tables: Employees and Salaries
- The employee's __name__ or __salary__ is missing.

```sql
(SELECT e.employee_id FROM Employees e 
    LEFT JOIN Salaries s ON e.employee_id = s.employee_id
    WHERE s.salary IS NULL)
UNION 
(SELECT s.employee_id FROM Salaries s
    LEFT JOIN Employees e ON e.employee_id = s.employee_id
    WHERE e.name is NULL)
ORDER BY employee_id;
```

## 1795. Rearrange Products Table

- original table: | product_id | store1 | store2 | store 3|
- rearranged table: | product_id | store | price |

```sql
SELECT product_id, 'store1' AS store, store1 AS price 
FROM Products 
WHERE store1 IS NOT NULL
UNION 
SELECT product_id, 'store2' AS store, store2 AS price 
FROM Products 
WHERE store2 IS NOT NULL
UNION 
SELECT product_id, 'store3' AS store, store3 AS price 
FROM Products 
WHERE store3 IS NOT NULL
```

## 608. Tree Node

- use parent ID to determine is which kind of node

```sql
SELECT A.id AS 'id',
CASE
    WHEN p_id IS NULL
        THEN 'Root'
    WHEN EXISTS(SELECT * FROM Tree t WHERE t.p_id = A.id)
        THEN 'Inner'
    ELSE
        'Leaf'
END AS 'type'
FROM Tree AS A;
```

## 176. Second Highest Salary

```sql
SELECT
    (
        SELECT DISTINCT Salary 
        FROM Employee 
        ORDER BY Salary DESC
        LIMIT 1 OFFSET 1
    )
AS SecondHighestSalary;
```

# Day 5: Union 

## 175. Combine Two Tables

- combine Person and Address table

```sql
SELECT p.firstName, p.lastName, a.city, a.state
FROM Person p
LEFT JOIN Address a ON a.PersonId = p.personId;
```

## 1581. Customer Who Visited but Did Not Make Any Transactions

```sql
-- start from here
SELECT *
FROM Visits v
LEFT JOIN Transactions t ON v.visit_id = t.visit_id
WHERE t.transaction_id IS NULL;

-- group and count
SELECT customer_id,
    COUNT(transaction_id IS NULL) AS 'count_no_trans'
FROM Visits v
LEFT JOIN Transactions t ON v.visit_id = t.visit_id
WHERE t.transaction_id IS NULL
GROUP BY v.customer_id;
```

## 1148. Article Views I

- find all the authors that viewed at least one of their own articles.

```sql
SELECT author_id AS 'id'
FROM Views
WHERE author_id = viewer_id
GROUP BY author_id
ORDER BY author_id;
```


# Day 6: Union

# Day 7: Function

# Day 8: Function

# Day 9: Control of Flow

# Day 10: Where


