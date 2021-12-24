# Section 18 Databases Trigger

- SQL statements that are __AUTOMATICALLY RUN__ when a specific table is changed

## Triggers

- trigger_time
    - before
    - after
- trigger_event
    - insert 
    - update
    - delete
- table_name


```sql
-- syntax
CREATE TRIGGER trigger_name
    trigger_time trigger_event ON table_name FOR EACH ROW
    BEGIN
    -- ...
    END

-- example 1, a simple validation
DELIMITER $$
CREATE TRIGGER must_be_adult
    BEFORE INSERT ON users FOR EACH ROW
    BEGIN 
        IF NEW.age < 18
        THEN 
            SIGNAL SQLSTATE '45000'
                SET MESSAGE_TEXT = 'Must be an adult';
        END IF;
    END;
$$ 

DELIMITER ;


INSERT INTO users(username, age) VALUES("Yang", 14);
-- 執行結果: 
-- ERROR 1644 (45000): Must be an adult!

```

## explanation

- NEW

```sql
-- NEW.age: refers to data that is about to be inserted
```

- MySQL Errors
  - A numeric error code(1146)
    - MySQL-specific
  - A five-character SQLSTATE values
    - the values are taken from ANSI SQL and ODBC and are more standardized
  - A message string
    - textual description of the error

- SIGNAL SQLSTATE 

- SET MESSAGE_TEXT 

```sql
SELECT * FROM fjefjeqwq;
-- error code:
-- ERROR 1146 (42S02): Table 'trigger_demo.fjefjeqwq' doesn't exist

```