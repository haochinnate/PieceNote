# Linux Commands

- [快速linux指令教學](https://www.youtube.com/watch?v=-fzO7iWCSWY)

## Navigation

```sh
pwd # print working directory

open . # macos, 打開目前的資料夾
open / # 打開根目錄

ls # list
ls -a # 列出所在資料夾的檔案 (包含隱藏)
ls -l # 包含詳細資訊
ls / -al 

man ls # 查詢 ls 這個指令的用法
       # 看完之後 按 q 離開

cd # change directory
cd .. # 回到上一層
```

## File

```sh
mkdir newFolder # 建立資料夾

cat somefile.txt # 印出檔案內容

cp somefile.txt newLocation.txt # 複製檔案
cp -r newFolder copiedFolder # 複製檔案 (recursive)

rm somefile.txt # 刪除檔案
rm -r copiedFolder # 刪除檔案 (recursive)
rm -rf # 強制刪除

mv 123.txt f1 # 移動檔案 (剪下貼上)
mv 456.txt 654.txt # 用 mv 來重新命名檔案
```

## vim 

