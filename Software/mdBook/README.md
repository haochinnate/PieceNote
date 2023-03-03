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
mdbook -h
```

- 開始使用

