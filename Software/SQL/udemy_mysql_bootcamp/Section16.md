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