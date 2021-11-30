# Section 10: Revisiting Data Types

## Storing Text

### CHAR

- CHAR has a __fixed length__
- CHAR is faster for fixed length text

```sql

-- CHAR(3)
-- only 3 characters, right-padded with spaces to specified length

CREATE TABLE dogs(name CHAR(5), breed VARCHAR(10));
INSERT INTO dogs (name, breed) VALUES('bob', 'beagle');
INSERT INTO dogs (name, breed) VALUES('Princess Jane', 'Retriever');
SELECT * FROM dogs;

```

## DECIMAL

- 

```sql
-- DECIMAL(13, 2)
-- 13: Total number of Digits
-- 2: Digits after decimal
CREATE TABLE items(price DECIMAL(5,2));
INSERT INTO items (price) VALUES(7);
INSERT INTO items (price) VALUES(299999); -- save as 999.99

INSERT INTO items(price) VALUES(34.88);
INSERT INTO items(price) VALUES(289.9999); -- save as 290.00

INSERT INTO items(price) VALUES(1.9999); -- save as 2.00

```

