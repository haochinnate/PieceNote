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
