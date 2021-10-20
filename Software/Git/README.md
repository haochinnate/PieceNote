# Git and GitHub tutorial

- [Youtube 影片](https://www.youtube.com/watch?v=3fUbBnN_H2c)

## How Git Works 

- git commit: save point

![git push](/imgs/image1_Amigoscode.png)

![git pull](/imgs/image2_Amigoscode.png)

## Verify Installation

```sh
git --version
git --help
```

## Git Setup

```sh
git config --global user.name ""
git config --global user.email ""
git config --global color.ui auto
git config // 看可以設定哪些
git config -l // 列出設定的狀態
```

## Git Init

- __REPOSITORIES__ in git contain a collection of files of various different versions of a project

```sh
mkdir learning-git
cd learning-git
git init . // 初始化 repository, for brand new project
// 會有 .git 資料夾
```

## Git Add & Remove

- 先建立一些檔案

```sh
touch index.html // echo $null >> index.html
touch index.js
touch main.css
ls
```

- 查看狀態

```sh
git status
```

- 加入 git staging area

```sh
git add index.html
git status
// 也可以用 git add .
```

- 移除 

```sh
git rm --cached index.html
git status // 恢復成原狀
// git rm -r --cached .
```

- 在 learning-git 底下再新增資料夾 test 和檔案 test.js
  - cd test
  - git status: untrack 會有 __./__ 這項
  - git add . : 只會增加 test.js (因為在 test folder 中)
  - git add -A: 全部的檔案都會加入

## Commits

```sh
git commit -m "bootstrap project"
git status // 會顯示 nothing to commit
git log // 看 log
git show "hash of commit" // 看該 commit 的詳細資料
q // 跳出
```

- 對 index.js 做修改

```sh
git status // 會有 index.js 被修改過的訊息
git diff // 觀看差異
git add . // 把修改存入 stage 
git status
git commit -m "added console.log" // commit change
git log // 會變兩個
git show "hash of second commit" 
```



