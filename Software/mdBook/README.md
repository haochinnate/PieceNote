# mdBook

- [mdBook Documentation](https://rust-lang.github.io/mdBook/)

## rustup

- [rustup 官網](https://rustup.rs/)
- 安裝指令
```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

### 安裝時跳的資訊

> This path will then be added to your PATH environment variable by modifying the profile files located at:
  - /Users/qineria/.profile
  - /Users/qineria/.bash_profile
  - /Users/qineria/.zshenv

> You can uninstall at any time with rustup self uninstall and
these changes will be reverted.

### 安裝完成

> stable-x86_64-apple-darwin installed - rustc 1.67.1 (d5a82bbd2 2023-02-07)

> Rust is installed now. Great!

> To get started you may need to restart your current shell.
> This would reload your PATH environment variable to include
> Cargo's bin directory ($HOME/.cargo/bin).

> To configure your current shell, run:
> source "$HOME/.cargo/env"

### 測試安裝版本

```bash
rustc --version
# 執行結果:
# rustc 1.67.1 (d5a82bbd2 2023-02-07)
```

```bash
# 確認 PATH 變數
echo $PATH
# 會多加: Users/users/.cargo/bin
```

### linker

```bash
# install C compiler
xcode-select --install
```

## Rust Hello World

```rust
fn main() {
    println!("Hello, world!");
}
```

```bash
# cd to folder of main.rs
rustc main.rs # 如果執行此指令有 error, 則要安裝linker 

# install C compiler
xcode-select --install

# 執行
./main
```

- 執行結果如下圖


## cargo

- cargo: Rust's build system and package manager

- 確認版本
```bash
cargo --version
# 執行結果
# cargo 1.67.1 (8ecd4f20a 2023-01-10)
```

## install mdbook

```bash
cargo install mdbook
```

- 安裝完成圖片


```bash
# 測試command 
mdbook --version
mdbook -h # 或是 mdbook help
```

## create new book

```bash
# 移到想要放置的路徑下, name-of-book 也會是資料夾的名稱
mdbook init [name-of-book]

cd [name-of-book]

mdbook serve --open # 打開瀏覽器觀看目前書的內容, 修改內容會即時更新

# 終止: control + c
```

- book.toml
  - describing how to build your book 
  - [簡介](https://rust-lang.github.io/mdBook/guide/creating.html#booktoml) 與 [詳細設定](https://rust-lang.github.io/mdBook/format/configuration/index.html)
- SUMMARY.md 
  - 此檔案包含書中所有的章節, 要在這個list中才會被看到
  - 在 serve 下, 在 SUMMARY.md 中增加不存在的檔案, mdbook會自動幫忙生成
  - [詳細介紹](https://rust-lang.github.io/mdBook/format/summary.html)
- src 資料夾
  - 所有書本內容都放在這邊
  - 裡面所有的檔案都會包含在output中, 所以如果有圖片或其他static檔案, 可以都放在 src 底下

## Publishing a book

```bash
mdbook build # 在book.toml檔案那一層執行此指令

# 會產生 book 資料夾, 裡面包含書本的 html 內容, 就可以把這個資料夾放在 webserver 上
```