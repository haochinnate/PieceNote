# [SQL Database](https://www.w3schools.com/sql/sql_create_db.asp)

## Create DB

- used to create a new SQL database

```sql
-- syntax
CREATE DATABASE databaseName;

-- example
CREATE DATABASE testDB;
```

## Drop DB

- used to drop an existing SQL database

```sql
-- syntax
DROP DATABASE databaseName;

-- example
DROP DATABASE testDB;
```

## Backup DB

- used in SQL Server to create a full back up of an existing SQL database

```sql
-- syntax
BACKUP DATABASE databaseName 
TO DISK = 'filepath';

-- example
BACKUP DATABASE testDB
TO DISK = 'D:\backups\testDB.bak';
```

### Differential Backup

- only backs up the parts of the database that have changed since the last full database backup

```sql
-- example
BACKUP DATABASE testDB
TO DISK = 'D:\backups\testDB.bak';
WITH DIFFERENTIAL;
```

## Create Table

- used tp create a new table in a database

```sql
-- syntax
CREATE TABLE table_name (
    column1 datatype,
    column2 datatype,
    column3 datatype
    ...
);

-- example
CREATE TABLE Persons (
    PersonID int, 
    LastName varchar(255),
    FirstName varchar(255),
    Address varchar(255),
    City varchar(255)
);
```

### Create Table Using Another Table

- The new table gets the same column definitions.

- the new table will be filled with the existing values from the old table

```sql
-- syntax
CREATE TABLE new_table_name AS
    SELECT column1, column2, ...
    FROM existing_table_name
    WHERE ...;

-- example
CREATE TABLE TestTable AS 
SELECT customername, contactname
FROM Customers;

```

## Drop Table

- used to drop an existing table in a database

```sql
-- syntax 
DROP TABLE table_name;

-- example
DROP TABLE Shippers;
```

### TRUNCATE TABLE

- used to delete the data inside a table, but not the table itself

```sql
-- syntax
TRUNCATE TABLE table_name;
```

## Alter Table

- used to add, delete, or modify columns in an existing table

- also used to add and drop various constraints on an existing table

### ADD Column

```sql
-- syntax 
ALTER TABLE table_name 
ADD column_name datatype;

-- example
ALTER TABLE Customers
ADD Email varchar(255);
```

### DROP Column

```sql
-- syntax
ALTER TABLE table_name
DROP COLUMN column_name;

-- example
ALTER TABLE Customers
DROP COLUMN Email;
```

### ALTER/MODIFY Column

- to change the data type of a column in a table

```sql
-- syntax
ALTER TABLE table_name ALTER COLUMN column_name datatype;
ALTER TABLE table_name MODIFY COLUMN column_name datatype;
ALTER TABLE table_name MODIFY column_name datatype;

```

## Constraints

- used to specify rules for data in a table

- can be specified when the table is created with the __CREATE TABLE__ statement, or after the table is created with the __ALTER TABLE__ statement


```sql
-- syntax
CREATE TABLE table_name(
    column1 datatype constraint,
    column2 datatype constraint,
    column3 datatype constraint,
);

```

- following constraints are commonly used in SQL

### Not Null

- Ensures that a column cannot have a NULL value

- By default, a column can hold NULL values

```sql
-- example on CREATE TABLE
CREATE TABLE Persons (
    ID int NOT NULL,
    LastName varchar(255) NOT NULL,
    FirstName varchar(255) NOT NULL,
    Age int
);

-- example on ALTER TABLE
ALTER TABLE Persons
MODIFY Age int NOT NULL;
```

### Unique

- Ensures that all values in a column are different

- Both the __UNIQUE__ and __PRIMARY KEY__ constraints provide a guarantee for uniqueness for a column or set of columns

- A __PRIMARY KEY__ constraint automatically has a __UNIQUE__ constraint.

- You can have many __UNIQUE__ constraints per table, but only one __PRIMARY KEY__ constraint per table.

```sql
-- example on CREATE TABLE
CREATE TABLE Persons (
    ID int NOT NULL UNIQUE,
    LastName varchar(255) NOT NULL,
    FirstName varchar(255),
    Age int
);

CREATE TABLE Persons (
    ID int NOT NULL,
    LastName varchar(255) NOT NULL,
    FirstName varchar(255),
    Age int,
    UNIQUE (ID)
);
```

```sql
-- to name a UNIQUE constraint, and to define a UNIQUE constraint on multiple columns
CREATE TABLE Persons (
    ID int NOT NULL,
    LastName varchar(255) NOT NULL,
    FirstName varchar(255),
    Age int,
    CONSTRAINT UC_Person UNIQUE (ID,LastName)
);
```

```sql
-- example on ALTER TABLE
ALTER TABLE Persons ADD UNIQUE(ID);

-- name constraint
ALTER TABLE Persons ADD CONSTRAINT UC_Person UNIQUE (ID, LastName);
```

```sql
-- drop a UNIQUE Constraint
-- MySQL
ALTER TABLE Persons DROP INDEX UC_Person;

-- SQL Server/Oracle/MS Access
ALTER TABLE Persons DROP CONSTRAINT UC_Person
```

### Primary Key

- A combination of a __NOT NULL__ and __UNIQUE__. Uniquely identifies each row in a table

- A table can have only __ONE__ primary key; and in the table, this primary key can consist of single or multiple columns(fields)

```sql
-- example in CREATE TABLE(MySQL)
CREATE TABLE Persons (
    ID int NOT NULL,
    LastName varchar(255) NOT NULL,
    FirstName varchar(255),
    Age int,
    PRIMARY KEY(ID)
);

-- example in CREATE TABLE(SQL Server/Oracle/MS Access)
CREATE TABLE Persons (
    ID int NOT NULL PRIMARY KEY,
    LastName varchar(255) NOT NULL,
    FirstName varchar(255),
    Age int
);

-- naming of a PRIMARY KEY constraint, and defining on multiple columns
CREATE TABLE Persons (
    ID int NOT NULL,
    LastName varchar(255) NOT NULL,
    FirstName varchar(255),
    Age int,
    CONSTRAINT PK_Person PRIMARY KEY (ID, LastName)
);

```

```sql
-- example in ALTER TABLE
ALTER TABLE Persons ADD PRIMARY KEY (ID);

-- naming
ALTER TABLE Persons ADD CONSTRAINT PK_Person PRIMARY KEY (ID, LastName)
```

```sql
-- drop a PRIMARY KEY constraint(MySQL)
ALTER TABLE Persons DROP PRIMARY KEY;

-- drop a PRIMARY KEY constraint(SQL Server/Oracle/MS Access)
ALTER TABLE Persons DROP CONSTRAINT PK_Person;
```

### Foreign Key

- Uniquely identifies a row/record in another table

- is a key used to link two tables together

- A FOREIGN KEY is a field (or collection of fields) in one table that refers to the PRIMARY KEY in another table.

- The table containing the foreign key is called the child table

- The table containing the candidate key is called the referenced or parent table

- The __FOREIGN KEY__ constraint is used to prevent actions that would destroy links between tables

- The __FOREIGN KEY__ constraint also prevents invalid data from being inserted into the foreign key column, because it has to be one of the values contained in the table it points to.

```sql
-- example in CREATE TABLE(MySQL)
CREATE TABLE Orders (
    OrderID int NOT NULL,
    OrderNumber int NOT NULL,
    PersonID int, 
    PRIMARY KEY (OrderID),
    FOREIGN KEY (PersonID) REFERENCES Persons(PersonID)
);

-- example in CREATE TABLE(SQL Server/Oracle/MS Access)
CREATE TABLE Orders (
    OrderID int NOT NULL PRIMARY KEY,
    OrderNumber int NOT NULL,
    PersonID int FOREIGN KEY REFERENCES Persons(PersonID)
);

-- naming and defining on multiple columns
CREATE TABLE Orders (
    OrderID int NOT NULL,
    OrderNumber int NOT NULL,
    PersonID int,
    PRIMARY KEY (OrderID),
    CONSTRAINT FK_PersonOrder FOREIGN KEY (PersonID)
    REFERENCES Persons(PersonID)
);

```

```sql
-- example in ALTER TABLE
ALTER TABLE Orders 
ADD FOREIGN KEY (PersonID) REFERENCES Persons(PersonID);

-- naming and defining on multiple columns
ALTER TABLE Orders
ADD CONSTRAINT FK_PersonOrder
FOREIGN KEY (PersonID) REFERENCES Persons(PersonID);

```

```sql
-- drop a FOREIGN KEY constraint(MySQL)
ALTER TABLE Orders DROP FOREIGN KEY FK_PersonOrder;

-- drop a PRIMARY KEY constraint(SQL Server/Oracle/MS Access)
ALTER TABLE Orders DROP CONSTRAINT FK_PersonOrder;
```

### Check

- Ensures that all values in a column satisfies a specific condition

- Used to limit the value range that can by placed in a column

- If you define a __CHECK__ constraint on a single column it allows only certain values for this column.

- If you define a __CHECK__ constraint on a table it can limit the values in certain columns based on values in other columns in the row.

#### CHECK on CREATE TABLE

```sql
-- constaint on the "Age" column when the "Persons" table is created
-- and ensures that the age of a person must be 18, or older

-- MySQL
CREATE TABLE Persons(
    ID int NOT NULL, 
    LastName varchar(255) NOT NULL,
    FirstName varchar(255),
    Age int,
    CHECK (Age >= 18)
);


-- SQL Server/Oracle/MS Access
CREATE TABLE Persons(
    ID int NOT NULL, 
    LastName varchar(255) NOT NULL,
    FirstName varchar(255),
    Age int CHECK (Age >= 18)
);

```

```sql
-- naming of a CHECK constraint, and for defining a CHECK contraint on multiple columns

CREATE TABLE Persons(
    ID int NOT NULL,
    LastName varchar(255) NOT NULL,
    FirstName varchar(255),
    Age int,
    City varchar(255),
    CONSTRAINT CHK_Person CHECK (Age>=18 AND City = 'Sandnes')
);

```


#### CHECK on ALTER TABLE

```sql
-- To create a CHECK contraint on the "Age" column when the table is already created

-- MySQL/SQL Server/Oracle/MS Access
ALTER TABLE Persons
ADD CHECK (Age>=18);

-- naming of a CHECK contraint, and defining a CHECK contraint on multiple columns
ALTER TABLE Persons
ADD CONSTRAINT CHK_PersonAge CHECK (Age>=18 AND City='Sandnes');

```

#### DROP a CHECK constaint

```sql

-- SQL Server/Oracle/MS Access
ALTER TABLE Persons
DROP CONSTRAINT CHK_PersonAge;

-- MySQL
ALTER TABLE Persons
DROP CHECK CHK_PErsonAge;

```

### Default 

- Sets a default value for a column when no value is specified

- The default value will be added to all new records IF no other value is specified

#### DEFAULT on CREATE TABLE

```sql
-- sets a default value for the "City" column when the "Persons" table is created

CREATE TABLE Persons(
    ID int NOT NULL,
    LastName varchar(255) NOT NULL,
    FirstName varchar(255),
    Age int,
    City varchar(255) DEFAULT 'Sandnes'
);

-- DEFAULT constraint can also be used to insert system values, by using functions like GETDATE()
CREATE TABLE Orders(
    ID int NOT NULL,
    OrderNumber int NOT NULL,
    OrderDate date DEFAULT GETDATE()
);

```

#### DEFAULT on ALTER TABLE

```sql
-- To create a DEFAULT contraint on the "City" column when the table is already created

-- MySQL
ALTER TABLE Persons
ALTER City SET DEFAULT 'Sandnes';

-- SQL Server
ALTER TABLE Persons
ADD CONSTRAINT df_City
DEFAULT 'Sandnes' FOR City;

-- MS Access
ALTER TABLE Persons
ALTER COLUMN City SET DEFAULT 'Sandnes';

-- Oracle
ALTER TABLE Persons
MODIFY City DEFAULT 'Sandnes';

```

#### DROP a DEFAULT constaint

```sql

-- MySQL
ALTER TABLE Persons
ALTER City DROP DEFAULT;

-- SQL Server/Oracle/MS Access
ALTER TABLE Persons
ALTER COLUMN City DROP DEFAULT;

```

### Index

- CREATE INDEX statement is used to create indexes in tables

- Used to create and retrieve data from the database very quickly

```sql
-- CREATE INDEX syntax 
CREATE INDEX index_name
ON table_name (column1, column2, ...);

-- CREATE UNIQUE INDEX syntax
CREATE UNIQUE INDEX index_name
ON table_name (column1, column2, ...);

```

#### CREATE INDEX example 

```sql
CREATE INDEX idx_lastname
ON Persons (LastName);

-- create an index on combination of columns
CREATE INDEX idx_pname
ON Persons (LastName, FirstName);

```

#### DROP INDEX statement

```sql
-- MS Access
DROP INDEX index_name ON table_name;

-- SQL Server
DROP INDEX table_name.index_name;

-- DB2/Oracle
DROP INDEX index_name;

-- MySQL
ALTER TABLE table_name
DROP INDEX index_name;
```

## Auto Increment

- Allows a unique number to be generated automatically when a new record is inserted into a table

- Often this is the primary key field that we would like to be created automatically every time a new record is inserted

```sql
-- example (MySQL)
CREATE TABLE Persons (
    Personid int NOT NULL AUTO_INCREMENT,
    LastName varchar(255) NOT NULL,
    FirstName varchar(255),
    Age int,
    PRIMARY KEY (Personid)
);

-- use "AUTO_INCREMENT" key word to perform feature
```

```sql
-- let sequence start with another value
ALTER TABLE Persons AUTO_INCREMENT=100;
```

```sql
-- example (SQL Server)
Personid int IDENTITY(1,1) PRIMARY KEY -- start from 1, increment by 1

-- example (Access)
Personid AUTOINCREMENT PRIMARY KEY -- AUTOINCREMENT(10, 5)

-- example (Oracle)
-- create a sequence, and use it by sequence.nextval
CREATE SEQUENCE seq_person
MINVALUE 1
START WITH 1
INCREMENT BY 1
CACHE 10;

INSERT INTO Persons (Personid, FirstName, LastName)
VALUES (seq_person.nextval, 'Lars', 'Monsen')
```

## Dates 

### SQL Date Data Types

#### MySQL

- DATE: YYYY-MM-DD
- DATETIME: YYYY-MM-DD HH:MI:SS
- TIMESTAMP: YYYY-MM-DD HH:MI:SS
- YEAR: YYYY or YY

#### SQL Server

- DATE: YYYY-MM-DD
- DATETIME: YYYY-MM-DD HH:MI:SS
- SMALLDATETIME: YYYY-MM-DD HH:MI:SS
- TIMESTAMP: a unique number

### example

```sql
SELECT * FROM Orders WHERE OrderDate='2008-11-11'
-- if OrderDate type is DateTime, then result is empty
```

## Views

## Injection

## Hosting

## Data Types
