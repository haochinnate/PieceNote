# Day 1: Select

## 595. Big Countries

```sql
SELECT name, population, area FROM World 
WHERE area >= 3000000 OR population  >= 25000000;
```

## 1757. Recyclable and Low Fat Products

```sql
SELECT product_id FROM products 
WHERE low_fats = 'Y' AND recyclable = 'Y'
```

# 584. Find Customer Referee

```sql
SELECT name FROM Customer
WHERE referee_id != 2 OR referee_id IS NULL;
```

# 183. Customers Who Never Order

```sql
SELECT c.Name AS "Customers" from Customers c
WHERE c.Id NOT IN (SELECT o.CustomerId from Orders o)
```

# Day 2: Select and Order

# Day 3: String Processing Functions

# Day 3: String Processing Functions

# Day 4: Union and Select

# Day 5: Union 

# Day 6: Union

# Day 7: Function

# Day 8: Function

# Day 9: Control of Flow

# Day 10: Where


