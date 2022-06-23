# Git and GitHub tutorial

- [Youtube 影片](https://www.youtube.com/watch?v=3fUbBnN_H2c)
- repo 放在 haochinnate\learning-git

## Cheat sheet

- [GitHub](https://education.github.com/git-cheat-sheet-education.pdf)
- [By hbons](https://github.com/hbons/git-cheat-sheet)
- [Atlassian](https://www.atlassian.com/git/tutorials/atlassian-git-cheatsheet)
- [GitLab](https://about.gitlab.com/images/press/git-cheat-sheet.pdf)

## How Git Works 

- git commit: save point

![git push(/imgs/image1_Amigoscode.png)]

![git pull(/imgs/image2_Amigoscode.png)]

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
git config # 看可以設定哪些
git config -l # 列出設定的狀態
```

## Git Init

- __REPOSITORIES__ in git contain a collection of files of various different versions of a project

```sh
mkdir learning-git
cd learning-git
git init . # 初始化 repository, for brand new project
# 會有 .git 資料夾
```

## Git Add & Remove

- 先建立一些檔案

```sh
touch index.html # echo $null >> index.html
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
# 也可以用 git add .
```

- 移除 

```sh
git rm --cached index.html
git status # 恢復成原狀
# git rm -r --cached .
```

- 在 learning-git 底下再新增資料夾 test 和檔案 test.js
  - cd test
  - git status: untrack 會有 __./__ 這項
  - git add . : 只會增加 test.js (因為在 test folder 中)
  - git add -A: 全部的檔案都會加入

## Commits

```sh
git commit -m "bootstrap project"
git status # 會顯示 nothing to commit
git log # 看 log
git show "hash of commit" # 看該 commit 的詳細資料
q # 跳出
```

- 對 index.js 做修改

```sh
git status # 會有 index.js 被修改過的訊息
git diff # 觀看差異
git add . # 把修改存入 stage 
git status
git commit -m "added console.log" # commit change
git log # 會變兩個
git show "hash of second commit" 
```

- 還原修改 discard changes 

```sh
git restore index.js
git status
```

## Ammend Commits

- 修改 main.css

```sh
git status
git add .
git commit -m "ejeijiej"
git log
```

- 修改 commit 的 summary

```sh
git commit --amend -m "added body in main.css"
git log # 最後一筆 commit 的 summary 會變
```

## GitHub

- use "git push" to store git project in remote server
- 在 Github 建立新的 repository

```sh
git remote add origin git@github.com:haochinnate/learning-git.git

git branch # 看目前的 branch, 會顯示 * master
git branch -M main # 切換到 main branch
git push -u origin main # 會失敗
```

## SSH Keys setup

- 在 github avator 的 setting 中, 找 __SSH and GPG keys__, [參考連結](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)

```sh
ssh-keygen -t ed25519 -C "your_email@example.com"
# 存在 default 位置
# no passphrase

# 再執行, 會產生一個 Agent pid
eval "$(ssh-agent -s)"

# 把 private key 加入 ssh agent 
ssh-add ~/.ssh/id_ed25519

# 複製 ssh key 內容
clip < ~/.ssh/id_ed25519.pub

# 然後加到 github setting 中
```

## Git Push

```sh
git push -u origin main # 成功 push

# 新建一個 main.go 檔案
git status

git add . 
git status 
git commit -m "added main.go with empty main function"
git log
git push # 不用 -u origin main 了
```

## Git Pull

```sh
# 在 github 網頁中, 建立 README.md

# 現在看 log 還不會有建立 README 的 commit
git log

# pull 下來
git pull 

# 在網頁上編輯 main.go & commit, 再下一次
git pull

```

## Branches

- A __branch__ represents an independent line of development

```sh
# 看目前的 branch
git branch

# 看 remote server 的 branch
git branch -r

# 看所有 branches
git branch -a

# 建立 branch
git branch feature-a

# 切換到特定 branch
git checkout feature-a

# 切換到上一個 branch
git checkout -

# 在 feature-a branch 建立一個新的檔案
git status # 會有 untracked files
git add .
git commit -m "utils.js with todo"

git log # 看目前狀態
git checkout main
git log # 兩個 branch log 會不一樣
git checkout - # 再切回去

git push # 會有 error
git push --set-upstream origin feature-a # 成功 push

# 建立新 branch, 並切換過去
git checkout -b to-delete

git branch -a # 再看全部的 branch

git checkout - # 切回 main

git branch -d to-delete # 刪除 branch
```

## Pull Requests

- merging PR

```sh
git merge feature-a # 把 feature-a 的東西 merge 進當前的 branch

# 不過應該用 pull request 來處理

# 在 GitHub 網頁 選擇 Create Pull Request, 選擇從 feature-a 到 main

# 建立 pull request, 可以指定 label, reviewers 等等...

# 點選 "Merge pull request", 然後 "Confirm merge"

# 然後點選 "Delete branch"

# 回到 repo 就會看到 merge pull request 的 commit

git branch # 目前還會有 feature-a branch

git log --oneline # 簡潔一點的模式看 log, 目前local 的main 還沒有被改變

git pull 

git log --oneline # 此時 local 的 main 就有被改變了

git branch -d feature-a # 刪除 branch feature-a

git branch -a

```

## Git workflow

1. 從 main(master) 把最新的 changes pull回來
2. 建立新的 branch
  - git branch -b new-branch 
3. start coding, commits
4. rebase from main(master), 可能有 conflict
5. resolve conflict for each commits
6. push to remote
7. raise a pull request
8. approved, then merge pull request to main(master)

## Dealing with conflicts

```sh
# 建立新的branch 
git checkout -b feature-xyz

# 修改 index.html
git status

# add & commit & push
git add .
git commit -m "add some html"
git push --set-upstream origin feature-xyz

# 在網頁上, 在 feature-xyz branch 上的 index.html 編輯 

# 在local上, 在 feature-xyz branch 上的 index.html 編輯
# 產生 conflict 
git add .
git commit -m "add conflict paragraph"
git push # 會有失敗訊息

```

## Merging conflicts

```sh
git pull # 會有 auto merging 失敗的訊息, 需要解決然後再 commit
# 解決 conflict
git status # 會有一個 unmerged files index.html

git add .
git commit -m "resolved conflict"
git push # 可以成功 push
```

## Rebase

```sh
# 直接在 GitHub 網頁的 main branch 編輯 index.html 檔案
# 但內容跟 feature-xyz branch 中的 index.html 不一樣, 製造 conflict

git pull --rebase origin main
# 等同 git pull -r origin main

# 訊息會有 try merge conflict but failed

# 修改後
git add .
git rebase --continue # 會要輸入 commit message


git push # 會有 error, 因為 remote 不知道已經 rebase 過了
git push -f # 強制 push

```
