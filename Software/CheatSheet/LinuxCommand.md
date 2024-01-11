# Linux Commands

- [快速linux指令教學](https://www.youtube.com/watch?v=-fzO7iWCSWY)

## 基礎

```sh
# Super key(windows) + Escape # 登出

# 關閉GUI畫面
sudo systemctl stop gdm
sudo telinit 3

# 啟動GUI畫面
sudo systemctl start gdm
sudo telinit 5

# login/logout
ssh student@ubuntu

# halt 
shutdown -h
shutdown -r # reboot


```

## Navigation

```sh
pwd # print working directory

pushd /tmp # 將路徑 push 到 stack 中
popd 

open . # macos, 打開目前的資料夾
open / # 打開根目錄

ls # list
ls -a # 列出所在資料夾的檔案 (包含隱藏)
ls -l # 包含詳細資訊
ls / -al 

man ls # 查詢 ls 這個指令的用法
       # 看完之後 按 q 離開

tree # display a tree view of the filesystem

cd # change directory
cd .. # 回到上一層
cd $HOME
cd - # change to previous directory
```

## File

```sh
mkdir newFolder # 建立資料夾
rmdir # 移除資料夾, 資料夾要是空的
rm -rf # 移除資料夾與檔案

cat somefile.txt # 印出檔案內容
# tac # cat 從後面印
wc somefile.txt # word count

head somefile.txt 
tail somefile.txt
less -N somefile.txt # page 方式觀看, 按 space 會下一頁

cp somefile.txt newLocation.txt # 複製檔案
cp -r newFolder copiedFolder # 複製檔案 (recursive)

rm somefile.txt # 刪除檔案
rm -i filename.txt # 會互動式詢問
rm -r copiedFolder # 刪除檔案 (recursive)
rm -rf # 強制刪除
rm -rf dir2

mv 123.txt f1 # 移動檔案 (剪下貼上)
mv 456.txt 654.txt # 用 mv 來重新命名檔案

touch <filename>

```

### Standard File Streams

```sh

stdin # 0, <
stdout # 1, >
stderr # 2, 2>
do_something > all-output-file 2>&1

# pipeline
command1 | command2 | command3

```

## Searching for Files

```sh

locate # 
grep 

locate zip | grep bin
locate LFS300

find . -name "LSF300*"
find . -name "LSF300*" -ls

echo > LFS300
# 用 locate command 的話, 要 update database
sudo updatedb
# 再執行
locate LSF300


# wildcard
ls
ls *.out
ls bs?.out
du -sh a* # du: disk usage
du -sh a*log*
du -sh a[p-z]*
du -sh *.?.*

# find 更多例子
find /usr -name gcc
find /usr -type d -name gcc # d: directory
find . -type d -maxdepth 1
find /usr -type f -name gcc # f: regular files

# finds and removes files that ends with .swp
# {} 會放入每一個 find 的結果, 然後用 ; 分隔
find -name "*.swp" -exec rm {} ';'


# find files based on size/time
find / -ctime 3
find / -size 0
find . -newer btmp # 找比 btmp 更新的



```

## vim 

```sh

vim some.txt # 用 vim 打開一個檔案
:wq # 退出
```

## 其他

```sh
Ctrl + R ## 搜尋打過的指令, 往前尋找
Ctrl + S ## 往後搜尋
```

## package manager(package management system)

```sh
brew install 
apt install

brew install go 

# two levels:
# high level: apt-get   | zypper  yum
# low level:   dpkg     |     rpm      

# 列出 system 上所有的 packages
dpkg --list | less
dpkg --list | grep bzip2

dpkg --remove bzip2

apt-cache search wget2
apt-get install wget-dev
apt-get remove wget2
```

## documentation

```sh

# man page system
man socket
man -f socket # = whatis socket
man 7 socket 

info make # make utility (GNU info)

man --help # help options 

```


# Processes

## Type:

1. Interactive Processes
2. Batch Processes
3. Daemons
4. Threads
5. Kernel Threads


```sh

# list the process
ps 
ps lf
ps -elf | less

# process tree
pstree

# terminate process
kill -SIGKILL <pid>
kill -9 <pid>

# change priority
# 降低 priority
renice +5 <pid>   
# 提高 priority
sudo renice -5 <pid> 


# top utility
top 

# cron 
# min hr day month day_of_week command

# sleep
# sleep number[suffix]
```

# File operation 2

```sh

```