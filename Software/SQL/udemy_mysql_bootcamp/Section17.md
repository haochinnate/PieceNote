# Section 17: Building Our Web App

## Express

- [官網](https://expressjs.com/)

```sh
# 建立新資料夾 JoinUs, 並切過去
cd JoinUs

# 先做 npm init
npm init
name: join_us
entry point: app.js

# 安裝 express
npm install express --save
npm install mysql faker --save

```

- package.json

```js
{
  "name": "join_us",
  "version": "1.0.0",
  "description": "",
  "main": "app.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "author": "",
  "license": "ISC",
  "dependencies": {
    "express": "^4.17.2",
    "faker": "^5.5.3",
    "mysql": "^2.18.1"
  }
}
```

- app.js

```js
var express = require('express');
var app = express();

app.get("/", function(req, res) {
	res.send("Hello From Our WEB APP!");
})

app.listen(3000, function() {
	console.log('App listening on port 3000');
});
```

- 啟動

```sh
cd JoinUs
node app.js
```

## Connecting Express and MySQL

```js
var mysql = require('mysql');

var connection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    database: 'join_us'
});

app.get("/", function(req, res) {	
	var q = "SELECT COUNT(*) AS count FROM users";
    connection.query(q, function(err, results){
        if(err) throw err;
        var count = results[0].count; 
        // res.render("home", {count: count});
        res.send("total user: " + count);
    });
});
```


## Adding EJS template

- 安裝

```sj
npm install --save ejs
```

- 使用

```js
app.set("view engine", "ejs");

// 從 views 資料夾去找 home.ejs
res.render('home')

res.render("home", {count: count});
```

```ejs
<!-- <% = count %> -->

<p class="lead">Enter your email to join <strong><%= count %></strong> others on our waitlist. We are 100% not a cult. </p>
```

## Form

```js
app.post("/register", function(req, res){
    var person = {
        email: req.body.email
    };
    connection.query('INSERT INTO users SET ?', person, function(err, result) {
        // if (err) throw err;
        console.log(err);
        console.log(result);
        res.redirect("/");
    });
});
```

### bodyparser
  
```sh
npm install --save body-parser
```

```js
var bodyParser  = require("body-parser");
app.use(bodyParser.urlencoded({extended: true}));
// req.body.email
```

## Link to CSS

```js
app.use(express.static(__dirname + "/public"));
```