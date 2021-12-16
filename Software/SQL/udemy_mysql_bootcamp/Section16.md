# Section 16: Introducing Node

## Node in Goorm

```sh
node -v
# create app.js file, with content: console.log('Hello, world!');

# execute 
node app.js 
```

## package: Faker 

- install package

```sh
npm install faker
```

- create fake users

```js
var faker = require('faker');

// faker.internet.email()
// faker.date.past()
// faker.address.streetAddress();
// faker.address.city()
// faker.address.state()

function generateAddress() {
    console.log(faker.address.streetAddress());
    console.log(faker.address.city());
    console.log(faker.address.state());
}

generateAddress();

for(var i = 0; i < 500; i++) {
    // insert a new user into the database
    console.log(faker.internet.email());
    console.log(faker.date.past());
}
```

## package: MySQL

```sql
CREATE DATABASE join_us;
use join_us;
SELECT CURDATE();
```

```sh
# talks to MySQL
npm install mysql
```

```js
// create connection
var mysql = require('mysql');

var connection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    database: 'join_us'
});

// run queries
var q = 'SELECT CURDATE()';
connection.query(q, function (error, results, fields) {
    if (error) throw error;
    console.log('the solution is: ',  results)
});

// close connection
connection.end();


// other examples
var q = 'SELECT 1 + 5 AS answer';
console.log('the solution is: ',  results[0].answer)

var q = 'SELECT CURTIME() AS time, CURDATE() AS date, NOW() AS now';
connection.query(q, function (error, results, fields) {
    if (error) throw error;
    console.log('Time: ',  results[0].time);
	console.log('Date: ',  results[0].date);
	console.log('Now: ',  results[0].now);
});
```

## create table and interactive with it

```sql
CREATE TABLE users(
    email VARCHAR(255) PRIMARY KEY,
    created_at TIMESTAMP DEFAULT NOW()
);

DESC users;

INSERT INTO users(email) VALUES
('Katie34@yahoo.com'), ('Tunde@gmail.com');
```


```js
var q = 'SELECT * FROM users';
connection.query(q, function (error, results, fields) {
    if (error) throw error;
    console.log(results);
    console.log(results[1].email);
});

// query total number of users
var q = 'SELECT COUNT(*) AS total FROM users';
console.log(results[0].total);

```

## Inserting data using node

```js
// take 1
var q = 'INSERT INTO users (email) VALUES ("someemail@gmail.com")';
connection.query(q, function (error, results, fields) {
    if (error) throw error;
    console.log(results);    
});

// take 2
var person = { email: 'Jenny467@gmail.com' };
connection.query('INSERT INTO users SET ?', person, function(error, result) {
    if (error) throw error;
    console.log(result); 
});

// take 3, dynamically
var person = { 
    email: faker.internet.email(), 
    created_at: faker.date.past() 
};
connection.query('INSERT INTO users SET ?', person, function(error, result) {
    if (error) throw error;
    console.log(result); 
});

// mysql package 會自己轉 faker.date 的格式

```

```sql

```
