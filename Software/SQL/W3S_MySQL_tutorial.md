# Intro

[W3Schools - SQL Tutorial](https://www.w3schools.com/sql/default.asp)
[W3Schools - MySQL Tutorial](https://www.w3schools.com/mysql/default.asp)
- SQL: Structured Query Language
- lets you access and manipulate databases

- SQL keywords are __NOT__ case sensitive: select is the name as SELECT

- [](https://www.mysqltutorial.org/mysql-cheat-sheet.aspx)
- [](https://devhints.io/mysql)
- [](https://www.interviewbit.com/mysql-cheat-sheet/)

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

```sql

```


# SELECT

- used to select data from a database
- data returned is stored in a result table, called the result-set

```sql

-- syntax
SELECT column1, column2 FROM table_name;

-- example
SELECT * FROM Customers;
SELECT CustomerName, City, Country FROM Customers;
```

## SELECT DISTINCT

- used to return only __distinct (different)__ values

```sql
-- syntax
SELECT DISTINCT column1, column2 FROM table_name; 

-- 沒有DISTINCT 的話, 會有91筆資料, 加了DISTINCT 回傳結果剩 21筆資料
SELECT DISTINCT Country FROM Customers;

-- 搭配 COUNT 直接計算數字, 結果是 21
SELECT COUNT(DISTINCT Country) FROM Customers;
```

# WHERE

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

## operators in WHERE

- __WHERE__ 不只可以用在 SELECT, 也可以用在 UPDATE, DELETE 等等statement
- 可以搭配下列 operator 使用
    - =, >, <, >=, <=
    - BETWEEN: between a certain range
    - LIKE: search for a pattern
    - IN: to specify multiple possible values for a column

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

# Logical operators(AND, OR and NOT)

- WHERE 還可以搭配 AND, OR, NOT

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

# ORDER BY

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

# INSERT INTO

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

# NULL Values

- A field with a NULL value is a field __with no value__
- 如果 field 是 optional的, 在 new 或 update 的時候就可以不指定值, 此時就是存 NULL Value

## test for NULL values

```sql
-- IS NULL syntax 
SELECT columns_names FROM table_name WHERE column_name IS NULL;

-- IS NOT NULL syntax
SELECT columns_names FROM table_name WHERE column_name IS NOT NULL;

-- example
SELECT CustomerName, ContactName, Address FROM Customers WHERE Address IS NULL;
```

# UPDATE

- used to modify the existing records in a table

```sql
-- syntax, 如果沒有使用 WHERE, 所有的data都會更新
UPDATE table_name SET column1 = value1, column2 = value2 WHERE condition;

-- example
UPDATE Customers SET ContactName = 'Alfred Schmidt', City = 'Frankfurt'
WHERE CustomerID = 1;
```

# DELETE FROM

- used to delete existing records in a table

```sql
-- syntax, 如果沒有使用 WHERE, 所有的data都會刪除
DELETE FROM table_name WHERE condition;

-- example
DELETE FROM Customers WHERE CustomerName = 'Alfreds Futterkiste';

-- delete all records
DELETE FROM Customers;
```

# LIMIT

- to specify the number of records to return.

```sql
-- syntax
SELECT column_name(s) FROM table_name WHERE condition LIMIT number;

-- example
SELECT * FROM Customers LIMIT 3;
```

## SELECT TOP, LIMIT, ROWNUM

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

# MIN() and MAX()

- returns the smallest/largest value of the selected column

```SQL
-- syntax
SELECT MIN(column_name) FROM table_name WHERE condition;
SELECT MAX(column_name) FROM table_name WHERE condition;

-- example, 只會回傳一個值
SELECT MIN(Price) AS SmallestPrice FROM Products;
SELECT MAX(Price) AS LargestPrice FROM Products;
```

# COUNT(), AVG(), SUM()

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

# LIKE

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

## Wildcards Example

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

# IN

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

# BETWEEN

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
```


## NOT BETWEEN

```sql
SELECT * FROM Products 
WHERE Price NOT BETWEEN 10 AND 20;
```

## BETWEEN (Text values)

```sql
-- Text values example
SELECT * FROM Products
WHERE ProductName BETWEEN 'Carnarvon Tigers' AND 'Mozzarella di Giovanni'
ORDER BY ProductName;
```

## BETWEEN (Dates example)

```sql
-- Dates example
SELECT * FROM Orders WHERE OrderDate BETWEEN #01/07/1996# AND #31/07/1996#;
SELECT * FROM Orders WHERE OrderDate BETWEEN '1996-07-01' AND '1996-07-31';
```

# Alias

- used to give a table, or a column in a table, a temporary name

- often used to make column names more readable

- alias only exists for the duration of the query


## Alias Column 
```sql
-- Syntax
SELECT column_name AS alias_column_name FROM table_name;

-- example
SELECT CustomerID AS ID, CustomerName AS Customer FROM Customers;

-- 如果 alias 有 空白, 那就要用 " " or ' ' 包起來 (有些是用 [])
SELECT CustomerName AS Customer, ContactName AS "Contact Person" FROM Customers;

-- alias name Address, combine four columns(Address, PostalCode, City and Country)
SELECT CustomerName, CONCAT_WS(', ', Address, PostalCode, City, Country) AS Address
FROM Customers

```

## Alias Table

```sql
-- Syntax
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

# Join

- [link](./W3S_MySQL_Join.md)

# UNION

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
-- 'Customer' 跟 'Supplier' 變成 Type 這個 column 的值
SELECT 'Customer' AS Type, ContactName, City, Country
FROM Customers
UNION
SELECT 'Supplier', ContactName, City, Country
FROM Suppliers;

```

# GROUP BY

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

# HAVING 

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
HAVING COUNT(CustomerID) > 5
ORDER BY COUNT(CustomerID) DESC;
```

# EXISTS

- is used to test for the existence of any record in a subquery
- return TRUE if the subquery returns one or more records

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

# ANY

- 回傳 boolean 做為 result
- 如果 subquery 的值, 有任何一個滿足條件的話, 就會回傳 TRUE

```sql
-- syntax
SELECT column_name(s)
FROM table_name
WHERE column_name operator ANY
(
    -- subquery
);

-- example
SELECT ProductName
FROM Products
WHERE ProductID = ANY
  (SELECT ProductID
  FROM OrderDetails
  WHERE Quantity = 10);
```

# ALL

- 回傳 boolean 做為 result
- 如果 subquery 的值, 所有都有滿足條件的話, 就會回傳 TRUE
- 和 SELECT, WHERE, HAVING 一起使用

```sql
-- syntax
SELECT ALL column_name(s) 
FROM table_name
WHERE condition;

SELECT column_name(s) 
FROM table_name
WHERE column_name operator ALL
(
    -- subquery
);

-- example
SELECT ProductName
FROM Products
WHERE ProductID = ALL
  (SELECT ProductID
  FROM OrderDetails
  WHERE Quantity = 10);
```

# INSERT INTO SELECT

- 從一個 table 複製資料並 insert 到另一個 table 中
- source 跟 target table 的 data types 需一致

```sql
-- syntax
INSERT INTO table2
SELECT * FROM table 
WHERE condition;

INSERT INTO table2 (column1, column2, column3, ...)
SELECT column1, column2, column3, ...
FROM table1
WHERE condition;

-- example
INSERT INTO Customers (CustomerName, City, Country)
SELECT SupplierName, City, Country FROM Suppliers
WHERE Country='Germany';
```

# CASE

- 如果 沒有 ELSE 部分, 也沒有任何 condition 符合, 則會回傳 NULL

```sql
-- syntax
CASE
    WHEN condition1 THEN result1
    WHEN condition2 THEN result2
    WHEN conditionN THEN resultN
    ELSE result
END;

-- example
SELECT OrderID, Quantity,
CASE
    WHEN Quantity > 30 THEN 'The quantity is greater than 30'
    WHEN Quantity = 30 THEN 'The quantity is 30'
    ELSE 'The quantity is under 30'
END AS QuantityText
FROM OrderDetails;

SELECT CustomerName, City, Country
FROM Customers
ORDER BY
(CASE
    WHEN City IS NULL THEN Country
    ELSE City
END);
```

# IFNULL & COALESCE

- let you return an alternative value if an expression is NULL

```sql
SELECT ProductName, 
    UnitPrice * (UnitsInStock + IFNULL(UnitsOnOrder, 0))
FROM Products;

SELECT ProductName, 
    UnitPrice * (UnitsInStock + COALESCE(UnitsOnOrder, 0))
FROM Products;
```


# Stored Procedures

- A stored procedure is a prepared SQL code that you can save, so the code can be reused over and over again.

```sql
-- Stored Procedure Syntax
CREATE PROCEDURE procedureName AS sql_statement GO;

-- Execute a Stored Procedure Syntax
EXEC procedureName;

-- Example
CREATE PROCEDURE SelectAllCustomers AS 
SELECT * FROM Customers
GO;

EXEC SelectAllCustomers;
```

- Stored procedure with one parameter

```sql
-- stored 
CREATE PROCEDURE SelectAllCustomers @City nvarchar(30)
AS
SELECT * FROM Customers WHERE City = @City
GO;

-- execute 
EXEC SelectAllCustomers @City = 'London';
```

- Stored Procedure With Multiple Parameters

```sql
-- stored 
CREATE PROCEDURE SelectAllCustomers @City nvarchar(30), @PostalCode nvarchar(10)
AS
SELECT * FROM Customers WHERE City = @City AND PostalCode = @PostalCode
GO;

-- example 
EXEC SelectAllCustomers @City = 'London', @PostalCode = 'WA1 1DP';
```