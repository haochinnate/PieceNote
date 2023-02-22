# Intro

- used to combine rows from two or more tables, based on a related column between them

```sql
-- example
SELECT Orders.OrderID, Customers.CustomerName, Orders.OrderDate
FROM Orders
INNER JOIN Customers ON Orders.CustomerID = Customers.CustomerID
```

# Different Types of SQL JOINs

- (INNER) JOIN 
    - returns records that have matchine values in both tables (即table1 交集 table2)
- LEFT (OUTER) JOIN
    - returns all records from the left table, and the matched records from the right talbe (即 交集部分 加上 table1原先的資料)
- RIGHT (OUTER) JOIN
    - returns all records from the right table, and the matched records from the left talbe (即 交集部分 加上 table2原先的資料)
- CROSS JOIN 
    - (FULL (OUTER) JOIN): returns all records when there is a match in either left or right table (即 table1 聯集 table2)

# INNER JOIN

- selects records that have matching values in both tables

```sql
-- syntax
SELECT column_name(s) FROM table1 
INNER JOIN table2 ON table1.column_name = table2.column_name;

-- example
SELECT Orders.OrderID, Customers.CustomerName, Shippers.ShipperName
FROM ((Orders
    INNER JOIN Customers ON Orders.CustomerID = Customers.CustomerID)
        INNER JOIN Shippers ON Orders.ShipperID = Shippers.ShipperID);
```

# LEFT JOIN

- if there is no match, the result is NULL from the right side

```sql
-- syntax
SELECT column_name(s) FROM table1 
LEFT JOIN table2 
ON table1.column_name = table2.column_name;

-- example
SELECT Customers.CustomerName, Orders.OrderID
FROM Customers
LEFT JOIN Orders ON Customers.CustomerID = Orders.CustomerID
ORDER BY Customers.CustomerName;
```

# RIGHT JOIN

- if there is no match, the result is NULL from the left side

```sql
-- syntax
SELECT column_name(s) FROM table1 
RIGHT JOIN table2 
ON table1.column_name = table2.column_name;

-- example
SELECT Orders.OrderID, Employees.LastName, Employees.FirstName
FROM Orders
RIGHT JOIN Employees ON Orders.EmployeeID = Employees.EmployeeID
ORDER BY Orders.OrderID;
```

# CROSS JOIN

- returns all records when there is a match in left (table1) or right (table2) table records.

```sql
-- syntax
SELECT column_name(s)
FROM table1
FULL OUTER JOIN table2
ON table1.column_name = table2.column_name
WHERE condition;

-- example
SELECT Customers.CustomerName, Orders.OrderID
FROM Customers
FULL OUTER JOIN Orders ON Customers.CustomerID=Orders.CustomerID
ORDER BY Customers.CustomerName;
```

# Self JOIN

- is a regulat join, but the table is joined with itself

```sql
-- syntax 
SELECT column_name(s) 
FROM table1 T1, table2 T2
WHERE condition;

-- example <> is != is NOT EQUAL
SELECT A.CustomerName AS CustomerName1, 
    B.CustomerName AS CustomerName2, 
    A.City
FROM Customers A, Customers B
WHERE A.CustomerID <> B.CustomerID
AND A.City = B.City
ORDER BY A.City;
```
