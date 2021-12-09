# Section 14: Instagram Database Clone

## Users Schema

```sql
-- id, username, created_at

CREATE DATABASE ig_clone;
USE ig_clone;

CREATE TABLE users(
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) UNIQUE NOT NULL,
    created_at TIMESTAMP DEFAULT NOW()
);

INSERT INTO users(username) VALUES
('Nick'),
('Joeman'),
('HowHow');

```

## Photos

```sql

-- id, image_url, user_id, created_at

CREATE TABLE photos(
    id INTEGER AUTO_INCREMENT PRIMARY KEY,
    image_url VARCHAR(255) NOT NULL,
    user_id INTEGER NOT NULL,
    created_at TIMESTAMP DEFAULT NOW(),
    FOREIGN KEY(user_id) REFERENCES users(id) 
);

INSERT INTO photos (image_url, user_id) VALUES
('/ejirjeir', 1),
('/erejiq', 2),
('/koko', 2)


SELECT photos.image_url, user.username FROM photos
JOIN users
    ON photos.user_id = users.id; 

```

## Comments

```sql

-- id, comment_text, user_id, photo_id, created_at
CREATE TABLE comments(
    id INTEGER AUTO_INCREMENT PRIMARY KEY,
    comment_text VARCHAR(255) NOT NULL,
    user_id INTEGER NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id),
    photo_id INTEGER NOT NULL,
    FOREIGN KEY(photo_id) REFERENCES photos(id),
    created_at TIMESTAMP DEFAULT NOW()
);


```

## Likes

```sql
CREATE TABLE likes(
    user_id INTEGER NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id),
    photo_id INTEGER NOT NULL,
    FOREIGN KEY(photo_id) REFERENCES photos(id),
    created_at TIMESTAMP DEFAULT NOW(),
    PRIMARY KEY(user_id, photo_id)
);

```

## Followers

```sql
CREATE TABLE follows(
    follower_id INTEGER NOT NULL,
    FOREIGN KEY(follower_id) REFERENCES users(id),
    followee_id INTEGER NOT NULL,
    FOREIGN KEY(followee_id) REFERENCES users(id),
    created_at TIMESTAMP DEFAULT NOW(),
    PRIMARY KEY(follower_id, followee_id)
);

```

## Tags

```sql

CREATE TABLE tags(
    id INTEGER AUTO_INCREMENT PRIMARY KEY,
    tag_name VARCHAR(255) UNIQUE,
    created_at TIMESTAMP DEFAULT NOW()
);


CREATE TABLE photos_tags(
    photo_id INTEGER NOT NULL,
    FOREIGN KEY(photo_id) REFERENCES photos(id),
    tag_id INTEGER NOT NULL,
    FOREIGN KEY(tag_id) REFERENCES tags(id),
    PRIMARY KEY(photo_id, tag_id)
);

```