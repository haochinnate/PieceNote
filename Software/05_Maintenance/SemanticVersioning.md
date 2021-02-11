# Semantic Versioning  

## References

- Semver.org [TW](https://semver.org/lang/zh-TW/), [EN](https://semver.org/)
- [SemVer-語意化版本規範](https://www.eebreakdown.com/2016/09/semver.html)
- [Introducing the npm semantic version calculator](https://blog.npmjs.org/post/115305091285/introducing-the-npm-semantic-version-calculator)

## Summary 摘要
版本格式: 主版號.次版號.修訂號(MAJOR.MINOR.PATCH)，版號增加的規則如下：

- 主版號(MAJOR): 當你做了不相容的 API 修改(incompatible API changes)
- 次版號(MINOR): 當你做了向下相容的功能性新增(backwards compatible manner)
- 修訂號(PATCH)：當你做了向下相容的問題修正(backwards compatible bug fixes)
- 先行版號(pre-release)及版本編譯資訊(build metadata) 可以加到MAJOR.MINOR.PATCH的後面，作為延伸。

## Specification 規範

### Public API

- 使用Semantic Versioning 控制的軟體「必須 MUST」定義公共 API。該 API 可以在程式碼中被定義或出現於嚴謹的文件內。無論何種形式都應該力求精確且完整。

### Normal version number

- 標準的版號「必須 MUST」採用 X.Y.Z 的格式
- 其中 X、Y 和 Z 為非負的整數
-「禁止 MUST NOT」在數字前方補零
- X 是主版號、Y 是次版號、而 Z 為修訂號
- 每個元素「必須 MUST」以數值來遞增。例如：1.9.1 -> 1.10.0 -> 1.11.0

### If released

- 標記版號的軟體發行後，「禁止 MUST NOT」改變該版本軟體的內容
- 任何修改都「必須 MUST」以新版本發行

### Initial Development

- 主版號為零（0.y.z）的軟體處於開發初始階段，一切都可能隨時被改變。
- 這樣的公共API 不應該被視為穩定版。

### Unstable to Stable

- 1.0.0 的版號用於界定公共 API 的形成。
- 這一版本之後所有的版號更新都基於公共 API及其修改內容。

### Patch Version 修訂號 

- 修訂號 Z（x.y.Z | x > 0）「必須 MUST」在只做了向下相容的修正(bug fixes)時才遞增。
- 此處修正是指 針對incorrect behavior而進行的內部修改(internal change)。

### Minor Version 次版號
- 次版號 Y（x.Y.z | x > 0）「必須 MUST」在有向下相容(backwards compatible)的新功能出現時遞增。
- 在任何公共 API 的功能被標記為棄用(deprecated)時也「必須 MUST」遞增。
- 也「可以 MAY」在內部程式有大量新功能或改進被加入時遞增，其中「可以 MAY」包括修訂級別的改變。
- 每當次版號遞增時，修訂號「必須 MUST」歸零。

### Major Version 主版本號

- 主版本號 X（X.y.z | X > 0）「必須 MUST」在有任何不相容的修改被加入公共 API 時遞增。
- 其中「可以 MAY」包括次版號及修訂級別的改變。
- 每當主版號遞增時，次版號和修訂號「必須 MUST」歸零。

### Pre-release Version 先行版號
- 先行版號「可以 MAY」被標注在修訂版之後，先加上一個連接號再加上一連串以句點分隔的標識符號來修飾。
- 標識符號「必須 MUST」由 ASCII 碼的英數字和連接號[0-9A-Za-z-] 組成，且禁止留白。
- 數字型的標識符號禁止在前方補零。Examples: 01, 001
- 先行版的優先級低於相關聯的標準版本。
- 被標上先行版號則表示這個版本並非穩定而且可能無法達到相容的需求。
- 範例：1.0.0-alpha、1.0.0-alpha.1、1.0.0-0.3.7、1.0.0-x.7.z.92。

### Build metadata 版本編譯資訊

- 版本編譯資訊「可以 MAY」被標注在修訂版或先行版號之後，先加上一個加號再加上一連串以句點分隔的標識符號來修飾。
- 標識符號「必須 MUST」由 ASCII 的英數字和連接號 [0-9A-Za-z-]組成，且禁止留白。
- 當判斷版本的優先層級時，版本編譯資訊「可 SHOULD」被忽略。
- 因此當兩個版本只有在版本編譯資訊有差別時，屬於相同的優先層級。
- 範例：1.0.0-alpha+001、1.0.0+20130313144700、1.0.0-beta+exp.sha.5114f85。

### Precedence, compare version

- 版本的優先層級指的是不同版本在排序時如何比較。
1. 判斷優先層級時，必須把版本依序拆分為主版號、次版號、修訂號及先行版號後進行比較（版本編譯資訊不在這份比較的列表中）。
2. 由左到右依序比較每個標識符號，第一個差異值用來決定優先層級：主版號、次版號及修訂號以數值比較，
    - 例如 1.0.0 < 2.0.0 < 2.1.0 < 2.1.1。
3. 當主版號、次版號及修訂號都相同時，改以優先層級比較低的先行版號決定。
    - 例如：1.0.0-alpha <1.0.0。
4. 有相同主版號、次版號及修訂號的兩個先行版號，其優先層級必須透過由左到右的每個被句點分隔的標識符號來比較，直到找到一個差異值後決定
    - 只有數字的標識符號以數值高低比較
    - 有字母或連接號時則逐字以 ASCII 的排序來比較
    - 數字的標識符號比非數字的標識符號優先層級低。
    - 若開頭的標識符號都相同時，欄位比較多的先行版號優先層級比較高。
    - 例如：1.0.0-alpha < 1.0.0-alpha.1 < 1.0.0-alpha.beta <1.0.0-beta < 1.0.0-beta.2 < 1.0.0-beta.11 < 1.0.0-rc.1 < 1.0.0。

## npm semver calculator

* [Online calculator](https://semver.npmjs.com/)

### caret(^)

- 例如: "^4.15.0"

> major 版本會是4, 且要 4.15.0 以上的版本 

### tilde(~)

- 例如: "~1.3.15"

> major.minor 是 1.3, 且要 1.3.15 以上的版本

### OR operator(||)

- just like OR

### 包含 pre-release 版本

- 篩選 semver range時, 預設不會將 pre-release 版本包含進來
- 如果要包含進來, 需要在 version number 中加入 pre-release tag
- 也可以加入 ">" comparator
- 例如 ">1.4.0-beta.0"





















