# Day 1: Select

## 595. Big Countries

- A country is big if:
    - it has an area of at least three million (i.e., 3000000 km2), or
    - it has a population of at least twenty-five million (i.e., 25000000).
- Write an SQL query to report the name, population, and area of the big countries.

```sql
SELECT name, population, area FROM World 
WHERE area >= 3000000 OR population  >= 25000000;
```

## 1757. Recyclable and Low Fat Products

- find the ids of products that are both low fat and recyclable.

```sql
SELECT product_id FROM products 
WHERE low_fats = 'Y' AND recyclable = 'Y'
```

## 584. Find Customer Referee

- report the names of the customer that are not referred by the customer with id = 2.

```sql
SELECT name FROM Customer
WHERE referee_id != 2 OR referee_id IS NULL;
```

## 183. Customers Who Never Order

- report all customers who never order anything.

```sql
SELECT c.Name AS "Customers" from Customers c
WHERE c.Id NOT IN (SELECT o.CustomerId from Orders o)
```

# Day 2: Select and Order

## 1873. Calculate Special Bonus

- calculate the bonus of each employee. 
- The bonus of an employee is 100% of their salary 
    - if the ID of the employee is an odd number and 
    - the employee name does not start with the character 'M'. 
    - The bonus of an employee is 0 otherwise.

```sql
SELECT employee_id,
CASE 
    WHEN name NOT LIKE 'M%' 
        AND employee_id % 2 != 0 THEN salary * 1
    ELSE 0
END AS 'bonus'
FROM employees
ORDER BY employee_id;
```

## 627. Swap Salary

- swap all 'f' and 'm' values (i.e., change all 'f' values to 'm' and vice versa) with a single update statement and no intermediate temporary tables.

```sql
UPDATE Salary SET sex = 
(CASE 
    WHEN sex = 'm' THEN 'f' 
    WHEN sex = 'f' THEN 'm' 
END);
```

## 196. Delete Duplicate Emails

- delete all the duplicate emails, keeping only one unique email with the smallest id

```sql
DELETE p1 FROM Person p1, Person p2 
WHERE p1.email = p2.email AND p1.id > p2.id;
```

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

## 197. Rising Temperature

- find all dates' Id with higher temperatures compared to its previous dates (yesterday).

```sql
SELECT w2.id FROM Weather w1,Weather w2
WHERE datediff(w2.recordDate, w1.recordDate) = 1 
AND w2.temperature > w1.temperature;
```

## 607. Sales Person

- report the names of all the salespersons who did not have any orders related to the company with the name "RED".

```sql
SELECT s.name
FROM SalesPerson s
WHERE s.sales_id NOT IN (
    SELECT o.sales_id
    FROM Orders o
    LEFT JOIN Company c 
        ON o.com_id = c.com_id
    WHERE c.name = "RED"
);
```

# Day 7: Function

## 1141. User Activity for the Past 30 Days I

- find the daily active user count for a period of 30 days ending 2019-07-27 inclusively. 
- A user was active on someday if they made at least one activity on that day.

```sql
SELECT activity_date AS 'day',
    COUNT(DISTINCT user_id) AS 'active_users'
FROM Activity
WHERE datediff('2019-07-27', activity_date) < 30
    AND activity_date <= '2019-07-27'
GROUP BY activity_date;
```

## 1693. Daily Leads and Partners

- for each date_id and make_name, return the number of distinct lead_id's and distinct partner_id's.

```sql
SELECT date_id, make_name,
    COUNT(DISTINCT lead_id) AS 'unique_leads', 
    COUNT(DISTINCT partner_id) AS 'unique_partners'
FROM DailySales
GROUP BY date_id, make_name
```

## 1729. Find Followers Count

- for each user, return the number of followers.
- Return the result table ordered by user_id in ascending order.

```sql

SELECT user_id, 
    COUNT(follower_id) AS 'followers_count'
FROM Followers
GROUP BY user_id
ORDER BY user_id;
```

# Day 8: Function

## 586. Customer Placing the Largest Number of Orders

- find the customer_number for the customer who has placed the largest number of orders.

```sql
SELECT customer_number 
FROM Orders
GROUP BY customer_number
ORDER BY COUNT(*) DESC LIMIT 1;
```

## 511. Game Play Analysis I

- report the first login date for each player.

```sql
SELECT player_id, MIN(event_date) AS 'first_login'
FROM Activity
GROUP BY player_id;
```

## 1890. The Latest Login in 2020

- report the latest login for all users in the year 2020. Do not include the users who did not login in 2020.

```sql
SELECT user_id, MAX(time_stamp) AS 'last_stamp'
FROM Logins
WHERE time_stamp LIKE '2020%'
GROUP BY user_id;
```

## 1741. Find Total Time Spent by Each Employee

- calculate the total time in minutes spent by each employee on each day at the office. 
- Note that within one day, an employee can enter and leave more than once. The time spent in the office for a single entry is out_time - in_time.

```sql
SELECT event_day AS 'day',
    emp_id,
    SUM(out_time - in_time) AS 'total_time'
FROM Employees
GROUP BY day, emp_id;
```

# Day 9: Control of Flow

# Day 10: Where


