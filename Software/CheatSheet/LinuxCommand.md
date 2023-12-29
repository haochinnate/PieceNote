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
rm -r copiedFolder # 刪除檔案 (recursive)
rm -rf # 強制刪除

mv 123.txt f1 # 移動檔案 (剪下貼上)
mv 456.txt 654.txt # 用 mv 來重新命名檔案

touch <filename>

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

## package manager

```sh
brew install 
apt install

brew install go 
```
