# Basic Commands

```sh
# check the installation
git --version

# initialize local git repository
git init 

# add files(s) to index(storaging area)
git add <file>

# check status of working tree
git status

# commit changes in index
git commit
```

# with remote repository
```sh
# push to remote repository
git push

# pull latest from remote repository
git pull

# clone repository into a new directory
git clone

```

# practice 1

- initial and add

```sh
# create and cd to myapp folder
touch index.html
touch app.js

git init 

git config --global user.name 'name'
git config --global user.email 'name@gmail.com'

git add index.html
git status # index.html is added, app.js is untracked

git rm --cached index.html
git status # index.html and app.js are both untracked

git add *.html # another way to add file(s)
git status # index.html is added, app.js is untracked

git add . # add everything in the folder
git status

```

- modify and commit

```sh

# 修改 index.html

git status # index.html will be modified
git add . # index.html back to staged area

git commit # will open vim editor to input commit message ("i" to insert mode, ESC to leave insert mode, ":wq" to finish commit) 
git status # nothing to commit

# 修改 app.js
git status # app.js will be modified
git add .
git commit -m 'change app.js' # commit with message directly 

```

- ignore file and directory

```sh

touch .gitignore # content: log.txt /dir2
# create file log.txt, and add some content 
git add . 
git status # only .gitignore file is in staged

```

- Branch and merge


```sh

git branch login # create branch
git checkout login # switch to some branch

# create new file login.html in login branch
# modify index.html

# commit in login branch
git add . 
git commit -m 'login form'
git status


git checkout master # switch back to master branch

git merge login # merge login to master, this will also open vim editor

```


- remote repository

```sh
# push an existing repository from the command line 
git remote add origin <URL.git>
git remote
git push -u origin master

# add new file in local repository
touch REAME.md
git add . 
git commit -m 'added readme'

# push to remote repository
git push 


# if someone else edited 
git pull

```

- clone repository

```sh
# 切換到想要放置 repository 的資料夾
git clone <URL.git>
```


# git merge vs. rebase

- merge to master branch?
- rebase the feature branches?

## merge 

```sh
# branch status:
# master branch:    m1 - m2 - m3
#                        |
# feature branch:        m2 - f1 - f2
#
# master combined:  m1 - m2 - m3 - ??

git branch # check all branch
git log # see the log of master branch
git checkout feature # switch to feature branch
git log # see the log of feature branch

# add content for f2
git add . 
git commit -m 'f2'
git log # f2 -> f1 -> m2


git master # switch back to master branch 
git log # latest commit is m3
git merge feature # merge feature to master, but this will has problem
git merge --squash feature # summarize all the difference/change in the feature branch to the last commit, and then merge to master branch
# action result: Automatic merge went well; stopped before committing as requested
git commit -m 'feature and master merged'
git log # 'feature and master merged' -> m3 -> m2 -> m1


# RESULT
# master branch: 'feature and master merged' -> m3 -> m2 -> m1
# feature branch: f2 -> f1 -> m2

```

## rebase 

```sh

git branch # in the master branch
git log # m3 -> m2 -> m1 

git checkout feature # go to feature branch
git log # f1 -> m2 

# master branch:    m1 - m2 - m3
#                        |
# feature branch:        m2 - f1


git rebase master 
# action result: First, rewinding head to replay your work on top of it...Applying f1

git log # f1 -> m3 -> m2 (m3 automerge)
# rebase: 1. 查看兩個分支最後的一個相同的commit (及分支點 m2), 
#         2. 查看目前分支(feature)改動的地方 (f1), 暫存這些改動
#         3. 查看 master 分支有哪些新的改動 (m3), 將這些改動 apply 到 feature branch(feature branch forward 到 m3)
#         4. 再把 f1 apply 到 feature branch


# add content for f2
git add . 
git commit -m 'f2'
git log # f2 -> f1 -> m3 


git master # switch back to master branch 
# 兩個分支目前最新相同的地方是 m3
git rebase feature 
git log # f2 -> f1 -> m3 -> m2 -> m1

# should not use rebase in public repository!
# DO NOT rebase commits that exist outside your repository



# RESULT
# master branch:  f2 -> f1 -> m3 -> m2 -> m1
# feature branch: f2 -> f1 -> m3

```