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

### Default 

- Sets a default value for a column when no value is specified

### Index

- Used to create and retrieve data from the database very quickly


## Not Null

## Unique

## Primary Key

## Foreign Key

## Check

## Default 

## Index

## Auto Increment

## Dates 

## Views

## Injection

## Hosting

## Data Types
