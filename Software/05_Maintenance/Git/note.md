- [筆記 on Google drive](https://drive.google.com/drive/folders/0BzUPI2q-erA_bG5CMENIUUxWRlk?usp=sharing)

- [Git for Professionals Tutorial - Tools & Concepts for Mastering Version Control with Git](https://www.youtube.com/watch?v=Uszj_k0DGsg)

### Perfect Commit
  
1. Add the __right__ changes!

```sh
git add css/general.css
git diff index.html

# -p for patch level, 問每一段要不要加入變更
git add -p index.html

git status 
```

2. Compose a __good__ commit message!
  1. Subject = concise summary of what happened
  2. Body = more detailed explanation
    - What is now different than before?
    - What's the reason for the change?
    - Is there anything to watch out for / anything particularly remarkable?

```sh
git commit 

git log
```

### Branching Strategies

#### A Written Convention

- Need a written best practice of how work is ideally structured in your team - to avoid mistakes & collisions

- It helps to onboard new team members

#### Integrating Changes & Structuring Releases

1. Maintline Development
2. State, Release, and Feature Branches
  - Long-Running & Short-Lived Branches

- Long-Running: main/master, develop/production
  - exist through the complete lifetime of the project
  - often, they mirror "stages" in your dev life cycle
  - common convention: __no direct commits!__    
- Short-Lived: feature 
  - for new features, bug fixes, refactorings, experiments
  - will be deleted after integration (merge/rebase)


### Pull Requests

- is provide by Git playform
- for: Communicating About and Reviewing Code
- Fork: your personal copy of a git repository
- PR are always based on branches, not on individual commits

```sh
git clone https://github.com/gntr/rails.git

cd rails

# some changes

git branch test
git checkout test

git add README.md
git commit -m "silly little change"

git push --set-upstream origin test
```

### Merge Conflicts

- How to Undo a Conflict and Start Over

```sh
git merge --abort 

git rebase --abort 
```

### Merge vs. Rebase

```sh
# merge commit 

# rebase: A Straight Line of Commits
git rebase branch-B
# 1. remove all commit on branch-A, save temporarily 
# 2. get applies to new commits from branch-B
# 3. take back the commit in step 1, that branch-A has been rebased
# rebase will rewrite comment history
```

- __DO NOT__ use rebase on commits that you've already pushed/shared on a remote repository!
- Use rebase for cleaning up your local commit history before merging it into a shared team branch



