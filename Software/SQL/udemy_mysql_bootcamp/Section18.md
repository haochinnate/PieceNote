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
    END;

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
  - 45000: a wild card generic state, representing unhandled user-defined exception
- SET MESSAGE_TEXT 

```sql
SELECT * FROM fjefjeqwq;
-- error code:
-- ERROR 1146 (42S02): Table 'trigger_demo.fjefjeqwq' doesn't exist


-- sql 預設看到 ";" 會當作結束, 用 DELIMITER 把結束符號換成 $$, 
-- $$ 是個標示, 可以換成其他符號
-- 最後再用 DELIMITER ; 來復原

DELIMITER $$
-- CREATE TRIGGER code...
$$
DELIMITER ;
```

## Example 2

```sql
-- preventing IG self-follows with triggers
DELIMITER $$

CREATE TRIGGER prevent_self_follows
    BEFORE INSERT ON follows FOR EACH ROW
    BEGIN
        IF NEW.follower_id = NEW.followee_id
        THEN 
            SIGNAL SQLSTATE '45000'
                SET MESSAGE_TEXT = 'You cannot follow yourself';
        END IF;
    END;
$$
DELIMITER ;

INSERT INTO follows(follower_id, followee_id) VALUES(88,88);
-- ERROR 1644 (45000): You cannot follow yourself

```
