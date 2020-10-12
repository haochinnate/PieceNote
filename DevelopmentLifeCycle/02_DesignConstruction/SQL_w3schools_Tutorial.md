# [SQL Tutorial](https://www.w3schools.com/sql/default.asp)

## Intro and Syntax

- SQL: Structured Query Language
- lets you access and manipulate databases

```sql
SELECT * FROM Customers;
```

- SQL keywords are __NOT__ case sensitive: select is the name as SELECT

- Some of the most important SQL commands
    - SELECT: extracts data
    - UPDATE: updates data
    - DELETE: deletes data
    - INSERT INTO: inserts new data
    - CREATE DATABASE: creates a new database
    - ALTER DATABASE: modifies a database
    - CREATE TABLE: creates a new table
    - ALTER TABLE: modifies a table
    - DROP TABLE: deletes a table 
    - CREATE INDEX: creates an index (search key)
    - DROP INDEX: deletes an index


## SELECT

- data returned is stored in a result table, called the result-set

```sql
-- syntax
SELECT column1, column2 FROM table_name;

-- example
SELECT * FROM table_name;
```
- column are the __field__ names of the table you want to select data from

### SELECT DISTINCT

- used to return only __distinct (different)__ values

```sql
-- syntax
SELECT DISTINCT column1, column2 FROM table_name; 

-- 沒有DISTINCT 的話, 會有91筆資料, 加了DISTINCT 回傳結果剩 21筆資料
SELECT DISTINCT Country FROM Customers;

-- 搭配 COUNT 直接計算數字, 結果是 21
SELECT COUNT(DISTINCT Country) FROM Customers;
```

## WHERE

- used to __filter__ records
- to extract those records that fulfill a specified condition

```sql
-- syntax
SELECT column1, column2 FROM table_name WHERE condition;

-- example text fields
SELECT * FROM Customers WHERE Country='Mexico';

-- example numeric fields
SELECT * FROM Customers WHERE CustomerID=1;

```

-- __WHERE__ 不只可以用在 SELECT, 也可以用在 UPDATE, DELETE 等等statement

### operators in WHERE

- =: Equal
- <>: Not equal, or !=
- BETWEEN: Between a certain range
- LIKE: Search for a pattern
- IN: To specify multiple possible values for a column

```sql
-- = example
SELECT * FROM Products WHERE Price = 18;

-- <> example
SELECT * FROM Products WHERE Price <> 18;

-- BETWEEN example
SELECT * FROM Products WHERE Price BETWEEN 50 AND 70;

-- LIKE example, start with 's'
SELECT * FROM Customers WHERE City LIKE 's%';

-- IN example, City 是 Paris 或 London
SELECT * FROM Customers WHERE City IN ('Paris','London');
```

### Logical operators(AND, OR and NOT)

```sql
-- AND syntax
SELECT column1, column2
FROM table_name
WHERE condition1 AND condition2 AND condition3;

-- OR syntax
WHERE condition1 OR condition2 OR condition3;

-- NOT syntax
WHERE NOT condition;

-- example
SELECT * FROM Customers WHERE City = 'Berlin' 
    AND PostalCode = 12209;


SELECT * FROM Customers 
    WHERE City='Berlin' OR City='London';

SELECT * FROM Customers WHERE NOT City = 'Berlin';

```

## ORDER BY

- used to __sort__ the result-set in ascending or descending order
- 預設是 ascending 遞增, 用 __DESC__ 關鍵字來遞減

```sql
-- syntax
SELECT column1, column2 FROM table_name
ORDER BY column1, column2 ASC|DESC;

-- example
SELECT * FROM Customers ORDER BY Country;

SELECT * FROM Customers ORDER BY Country DESC;

SELECT * FROM Customers ORDER BY Country, CustomerName;

```

## INSERT INTO

- insert new records in a table

```sql
-- syntax 
INSERT INTO table_name (column1, column2, column3)
VALUES (value1, value2, value3)

-- example
INSERT INTO Customers (CustomerName, ContactName, Address, City, PostalCode, Country)
VALUES ('Cardinal', 'Tom B. Erichsen', 'Skagen 21', 'Stavanger', '4006', 'Norway');

-- 如果所有table 中columns 都有加入新值, 就不用指定 column, 但要確保順序是對的
INSERT INTO table_name
VALUES (value1, value2, value3)

-- example
INSERT INTO Customers (CustomerName, City, Country)
VALUES ('Cardinal', 'Stavanger', 'Norway');

```

## NULL Values

- A field with a NULL value is a field __with no value__
- 如果 field 是 optional的, 在 new 或 update 的時候就可以不指定值, 此時就是存 NULL Value

### test for NULL values

```sql
-- IS NULL syntax 
SELECT columns_names FROM table_name WHERE column_name IS NULL;

-- IS NOT NULL syntax
SELECT columns_names FROM table_name WHERE column_name IS NOT NULL;

-- example
SELECT CustomerName, ContactName, Address FROM Customers WHERE Address IS NULL;

```

## UPDATE

- used to modify the existing records in a table

```sql
-- syntax, 如果沒有使用 WHERE, 所有的data都會更新
UPDATE table_name SET column1 = value1, column2 = value2 WHERE condition;

-- example
UPDATE Customers SET ContactName = 'Alfred Schmidt', City = 'Frankfurt'
WHERE CustomerID = 1;


```

## DELETE FROM

- used to delete existing records in a table

```sql
-- syntax, 如果沒有使用 WHERE, 所有的data都會刪除
DELETE FROM table_name WHERE condition;

-- example
DELETE FROM Customers WHERE CustomerName = 'Alfreds Futterkiste';

-- delete all records
DELETE FROM Customers;

```

## Functions

### SELECT TOP, LIMIT, ROWNUM

- SELECT TOP, used to specify the number of records to return
- 不是所有的 db 都支援 SELECT TOP, 有些用 LIMIT, 有些用ROWNUM

```SQL
-- syntax
SELECT TOP number|percent column_name(s)
FROM table_name
WHERE condition;

SELECT column_name(s)
FROM table_name
WHERE condition
LIMIT number;

SELECT column_name(s)
FROM table_name
WHERE ROWNUM <= number;

-- example 
SELECT TOP 3 * FROM Customers;
SELECT * FROM Customers LIMIT 3;
SELECT * FROM Customers WHERE ROWNUM <= 3;

-- TOP PERCENT example
SELECT TOP 50 PERCENT * FROM Customers;

-- 搭配 WHERE 條件
SELECT TOP 3 * FROM Customers WHERE Country = 'Germany';

```

### MIN() and MAX()

- returns the smallest/largest value of the selected column

```SQL
-- syntax
SELECT MIN(column_name) FROM table_name WHERE condition;
SELECT MAX(column_name) FROM table_name WHERE condition;

-- example, 只會回傳一個值
SELECT MIN(Price) AS SmallestPrice FROM Products;
SELECT MAX(Price) AS LargestPrice FROM Products;
```

### COUNT(), AVG(), SUM()

- COUNT(): returns the number of rows that matches a specified criterion
- AVG(): returns the average value of a numeric column
- SUM(): returns the total sum of a numeric column

```sql
-- syntax
SELECT COUNT(column_name) FROM table_name WHERE conditon;
SELECT AVG(column_name) FROM table_name WHERE conditon;
SELECT SUM(column_name) FROM table_name WHERE conditon;

-- example
SELECT COUNT(ProductID) FROM Products;

SELECT AVG(Price) FROM Products;

SELECT SUM(Quantity) FROM OrderDetails;
```

## Like

- used in __WHERE__ to search for a specified pattern in a column 

- 2 wildcards often used in conjunction with the __LIKE__ operator
    - __%__: 0, 1, or multiple characters
    - **_**: a single character
    - (MS Access 用 __*__ 和 __?__)

- You can combine any number of conditions using __AND__ or __OR__ operators

```sql
-- syntax
SELECT column1, column2 FROM table_name WHERE columnN LIKE pattern;

-- example
SELECT * FROM Customers WHERE CustomerName LIKE 'a%';

SELECT * FROM Customers WHERE CustomerName LIKE '%a';

SELECT * FROM Customers WHERE CustomerName LIKE '_r%';

SELECT * FROM Customers WHERE CustomerName LIKE 'a__%';

SELECT * FROM Customers WHERE CustomerName NOT LIKE 'a%';
```

- Wildcards Example

| Like Operator | Description |
| ----------- | ----------- |
| WHERE columnN LIKE __'a%'__ | Finds any values that start with "a" |
| WHERE columnN LIKE __'%a'__| Finds any values that end with "a" |
| WHERE columnN LIKE __'%or%'__ | Finds any values that have "or" in any position |
| WHERE columnN LIKE __'_r%'__ | Finds any values that have "r" in the second position |
| WHERE columnN LIKE __'a_%'__ | Finds any values that start with "a" and are at least 2 characters in length |
| WHERE columnN LIKE **'a__%'** | Finds any values that start with "a" and are at least 3 characters in length |
| WHERE columnN LIKE __'a%o'__ | Finds any values that start with "a" and ends with "o" | 


## Wildcards

- Wildcard characters is used to substitute one or more characters in a string

- Wildcard characters are used with __LIKE__ operator

- Wildcard characters

| Symbol in MS Access | Symbol in SQL Server | Description | Example |
| ----------- | ----------- | ----------- | ----------- |
| * | % | Represents zero or more characters | __bl%__ finds bl, black, blue, and blob |
| ? | _ | Represents a single character | __h?t__, **h_t** finds hot, hat, and hit |
| [] | [] | Represents any single character within the brackets | __h[oa]t__ finds hot and hat, but not hit |
| ! | ^ | Represents any character not in the brackets | __h[!oa]t__, __h[^oa]t__ finds hit, but not hot and hat |
| - | - | Represents a range of characters | __c[a-b]t__ finds cat and cbt |
| # | N/A | Represents any single numeric character | 2#5 finds 205, 215, 225, 235, 245, 255, 265, 275, 285, and 295 |


```sql
-- example

-- starting with "ber"
SELECT * FROM Customers WHERE City LIKE 'ber%';

-- contain "es"
SELECT * FROM Customers WHERE City LIKE '%es%';

-- starting with any character(just one), endwith "ondon"
SELECT * FROM Customers WHERE City LIKE '_ondon';

-- starting with "b", "s" or "p"
SELECT * FROM Customers WHERE City LIKE '[bsp]%';

-- not starting with "b", "s" or "p"
SELECT * FROM Customers WHERE City LIKE '[!bsp]%';
SELECT * FROM Customers WHERE City NOT LIKE '[bsp]%';

-- starting with anything from "a" to "f"
SELECT * FROM Customers WHERE City LIKE '[a-f]%';

```

## In

- IN operator allows you to specify multiple values in a __WHERE__ clause

- IN operator is a shorthand for multiple __OR__ conditions

```sql
-- syntax 
SELECT column_name(s) FROM table_name WHERE column_name IN (value1, value2);

SELECT column_name(s) FROM table_name WHERE column_name IN (SELECT statement);

-- example
-- City == "Germany" or "France" or "UK"
SELECT * FROM Customers WHERE Country IN ('Germany', 'France', 'UK');

-- City != "Germany" or "France" or "UK"
SELECT * FROM Customers WHERE Country NOT IN ('Germany', 'France', 'UK');

-- selects all customers that are from the same countries as the suppliers:
SELECT * FROM Customers WHERE Country IN (SELECT Country FROM Suppliers);
```

## Between

- The BETWEEN operator selects values within a given range. The values can be numbers, text, or dates.

- The BETWEEN operator is inclusive: begin and end values are included. 


```sql
-- syntax 
SELECT column_name(s) FROM table_name WHERE column_name BETWEEN value1 AND value2

-- example
-- 10 <= Price <= 20
SELECT * FROM Products WHERE Price BETWEEN 10 AND 20;

-- Price < 10 or Price > 20
SELECT * FROM Products WHERE Price NOT BETWEEN 10 AND 20;

-- BETWEEN with IN 
SELECT * FROM Products WHERE Price BETWEEN 10 AND 20 
AND CategoryID NOT IN (1, 2, 3);

-- Text values example
SELECT * FROM Products
WHERE ProductName BETWEEN 'Carnarvon Tigers' AND 'Mozzarella di Giovanni'
ORDER BY ProductName;

-- Dates example
SELECT * FROM Orders WHERE OrderDate BETWEEN #01/07/1996# AND #31/07/1996#;

SELECT * FROM Orders WHERE OrderDate BETWEEN '1996-07-01' AND '1996-07-31';
```

## Alias

- used to give a table, or a column in a table, a temporary name

- often used to make column names more readable

- alias only exists for the duration of the query

```sql
-- Alias Column Syntax
SELECT column_name AS alias_column_name FROM table_name;

-- example
SELECT CustomerID AS ID, CustomerName AS Customer FROM Customers;

-- 如果 alias 有 空白, 那就要用 [ ] 包起來
SELECT CustomerName AS Customer, ContactName AS [Contact Person] FROM Customers;

-- alias name Address, combine four columns(Address, PostalCode, City and Country)
SELECT CustomerName, Address + ', ' + PostalCode + ' ' + City + ', ' + Country AS Address
FROM Customers

```

```sql
-- Alias Table Syntax
SELECT column_name(s) FROM table_name AS alias_table_name

-- Customers table -> c, Orders table -> o
SELECT o.OrderID, o.OrderDate, c.CustomerName
FROM Customers AS c, Orders AS o
WHERE c.CustomerName = 'Around the Horn' AND c.CustomerID=o.CustomerID;

```

- Aliases can be useful when:
    - There are more than one table involved in a query
    - Functions are used in the query
    - Column names are big or not very readable
    - Two or more columns are combined together

## Join

- used to combine rows from two or more tables, based on a related column between them

```sql
-- example
SELECT Orders.OrderID, Customers.CustomerName, Orders.OrderDate
FROM Orders
INNER JOIN Customers ON Orders.CustomerID = Customers.CustomerID

```

### Different Types of SQL JOINs

- (INNER) JOIN: returns records that have matchine values in both tables (即table1 交集 table2)
- LEFT (OUTER) JOIN: returns all records from the left table, and the matched records from the right talbe (即 交集部分 加上 table1原先的資料)
- RIGHT (OUTER) JOIN: returns all records from the right table, and the matched records from the left talbe (即 交集部分 加上 table2原先的資料)
- FULL (OUTER) JOIN: returns all records when there is a match in either left or right table (即 table1 聯集 table2)

### INNER JOIN

- selects records that have matching values in both tables

```sql
-- syntax
SELECT column_name(s) FROM table1 INNER JOIN table2 ON table1.column_name = table2.column_name;

-- example
SELECT Orders.OrderID, Customers.CustomerName, Shippers.ShipperName
FROM ((Orders
    INNER JOIN Customers ON Orders.CustomerID = Customers.CustomerID)
        INNER JOIN Shippers ON Orders.ShipperID = Shippers.ShipperID);

```

### LEFT JOIN

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

### RIGHT JOIN

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

### FULL JOIN

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

### Self JOIN

- is a regulat join, but the table is joined with itself

```sql
-- example
SELECT A.CustomerName AS CustomerName1, 
    B.CustomerName AS CustomerName2, 
    A.City
FROM Customers A, Customers B
WHERE A.CustomerID <> B.CustomerID
AND A.City = B.City
ORDER BY A.City;

```

## UNION Operator

- used to combine the result-set of two or more SELECT statements

- 每個 UNION 連結的 SELECT statement 都必須要有相同的 columns 數量
- columns 必須要有 similar data types
- columns 在 SELECT statement 也要有相同的順序

```sql
-- syntax
SELECT column_name(s) FROM table1
UNION
SELECT column_name(s) FROM table2

-- UNION 預設只會選擇 distinct values, 要允許 duplicate values 要使用 UNION ALL
SELECT column_name(s) FROM table1
UNION ALL
SELECT column_name(s) FROM table2

-- example
SELECT City FROM Customers
UNION ALL
SELECT City FROM Suppliers
ORDER BY City;

-- "AS Type" - it is an alias
SELECT 'Customer' AS Type, ContactName, City, Country
FROM Customers
UNION
SELECT 'Supplier', ContactName, City, Country
FROM Suppliers;

```

## Group By

- groups rows that have the same values into summary rows
- is often used with aggrefate functions(COUNT, MAX, MIN, SUM, AVG) to group the result-set by one or more columns

```sql
-- syntax
SELECT column_name(s)
FROM table_name
WHERE condition
GROUP BY column_name(s)
ORDER BY column_name(s);

-- example
SELECT COUNT(CustomerID), Country
FROM Customers
GROUP BY Country;

SELECT COUNT(CustomerID), Country
FROM Customers
GROUP BY Country
ORDER BY COUNT(CustomerID) DESC;

```

## Others Keyword

### HAVING 

- __HAVING__ was added because the __WHERE__ keyword could not be used with aggregate functions

```sql
-- syntax 
SELECT column_name(s)
FROM table_name
WHERE condition
GROUP BY column_name(s)
HAVING condition
ORDER BY column_name(s);

-- example
SELECT COUNT(CustomerID), Country
FROM Customers
GROUP BY Country
HAVING COUNT(CustomerID) > 5;

```

### EXISTS

- is used to test for the existence of any record in a subquery
* return true if the subquery returns one or more records

```sql
-- syntax
SELECT column_name(s)
FROM table_name
WHERE EXISTS
(SELECT column_name FROM table_name WHERE condition);

-- example
SELECT SupplierName
FROM Suppliers
WHERE EXISTS (SELECT ProductName FROM Products WHERE Products.SupplierID = Suppliers.supplierID AND Price < 20);

```

