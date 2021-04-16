
- [Reference](https://www.youtube.com/watch?v=Qw9zlE3t8Ko)

### Image

- is a template for the environment that you want to run
    - OS
    - Software
    - Application

### Container

- when you run an image, you get a container
- one container running the website, and another one container running the product service
- be independent, can be written in different languages

```cmd
docker build
docker run
```

### Docker Compose

- 每次都要這樣設定/run 很麻煩, 所以有 docker compose

- define all of our services in a configuration file, 一個 command 就執行所有需要的 container
- 建立檔案 dcoker-compose.yml

```yml
version: '3'

services: 
  product-service:
    build: ./product
    volumes:
      - ./product:/usr/src/app
    ports:
      - 5001:80
  website: 
    image: php:apache
    volumes:
      - ./website:/var/www/html
    ports:
      - 5000:80
    dependes_on:
      - product-service
```

- 執行 "docker-compose up"
- product-service 是用python寫, website 是用 php寫, 在 website 中去呼叫 product-service 來取得內容


