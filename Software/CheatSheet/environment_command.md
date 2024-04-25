# homebrew

```sh
# 確認安裝
brew -v

brew install [package]
brew list # 列出已安裝的套件

brew info [package]
brew search

brew update # 更新 homebrew
brew upgrade
```

# 安裝 pipenv

```sh
# 要先安裝 pyenv
brew install pyenv

pyenv install -l # 查看目前可以安裝的版本

pyenv version # 查看當前python版本
pyenv versions # 查看當前所有python 安裝版本

pyenv install miniconda3-4.3.30 
pyenv global miniconda3-4.3.30 # 設定成 global python 環境


conda env list
conda info --envs
```

# python 

```sh
python --version # 確認 python 版本

```

# conda

## 版本, 更新

```sh
conda -V # 版本 4.12.0

anaconda -V # 1.9.0

conda update conda 
# update 完還是 4.12.0

conda update -n base -c defaults conda
# update 完還是 4.12.0

conda update anaconda
# anaconda -V -> 1.12.3

conda clean --packages --tarballs
conda update --all

# Update the conda package manager to the latest version in your base environment
conda update -n base conda
# Use conda to update Anaconda to the latest version in your base environment
conda update -n base anaconda

# 都不行, 直接安裝新版本 anaconda, 
# conda -V -> 24.3.0

```
## env

```sh
# create new virtual environment

conda activate learn_da

python --version # -> 3.11.8

conda deactivate 

anaconda-navigator # 啟動 anaconda navigator

conda list -n learn_da # 列出 environment 中的 packages
```

# 爬蟲

## 步驟

1. 從 response 看有沒有我們要的資料
2. 看對應的 header, 他的 request URL 送出了什麼
3. 開發 crawler, crawler 會需要 parameter
4. 從 response 中擷取資料

