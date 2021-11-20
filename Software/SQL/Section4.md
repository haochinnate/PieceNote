# Section 4: Inserting data 

## Inserting Data

```sql
-- ORDER DOES MATTER!
INSERT INTO table_name(column_name) VALUES (data);
INSERT INTO cats(name, age) VALUES ('Jetson', 7);

SELECT * FROM cats;
```

## Multiple Insert

```sql

INSERT INTO cats(name, age) 
VALUES ('Charlie', 10),
       ('Sadie', 3),
       ('Lazy Bear',1);
```

- 輸入資料含引號
  - Escape the quotes with a backslash: "This text has \"quotes\" in it" or 'This text has \'quotes\' in it'
  - Alternate single and double quotes: "This text has 'quotes' in it" or 'This text has "quotes" in it'

## 


