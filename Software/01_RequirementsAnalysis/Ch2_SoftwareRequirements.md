## 第二章: 軟體需求

### 跨職能團隊

- 跨職能團隊可以有效地減短週期，將開發的過程變成多個「短週期」
- 做產品可以在團隊內做決定，可以將對外部的依賴降到最小，因此有能力用短週期來釋出產品。

1. 跨職能團隊擁有將想法轉化成最終產品的所有必要技能
2. 跨職能團隊是像團隊般一樣工作 (Work as a Team)
  - 彼此目標一致、__溝通沒有障礙__
3. 跨職能團隊的任務可以彼此互相支援
  - 不是強迫團隊的成員去做不擅長的事
4. 跨職能團隊要有共同的目標並納入績效評估

### 迷思破解

- 跨職能團隊的任務一定要有共同管理的部分
- 挑戰: 不同職能的人會在短週期內，有密集且不同專業角度的反饋 -> 所以需要有效率地進行需求溝通

### Cynefin Framework & 問題識別

- 核心觀念: 針對不同的問題情境, 採取不同的解決方案

- 問題分為: 有序(Ordered), 無序(Unordered), 困惑(Confused)
  - 有序: 事件的發生是可以預期 (Predictable) 的

- Ordered/Unordered情境可以拆分成四類, 用這四類來做 __問題識別__

#### 清楚 Clear/Obvious/Simple
 
- 應對策略：感知(Sense) -> 分類(Categorize) ->回應(Respond)
- 管理方式：固定型約束 (Fixed Constraint)
  - 直接規定要做什麼, 以什麼方式做, 直接制定標準作業流程

#### 繁雜 Complicated

- 感知(Sense) -> 分析(Analyze) -> 回應(Respond)
- 需要很多專家, 將繁雜的問題自動化變成清楚的問題
- 管理方式: 治理型約束 (Governing Constraint)
  - 在一個範圍內(訂定範圍與方向), 由專家自行決定要走的目標/要使用的解決方式, 但都是朝相同的方向前進

#### 複雜 Complex

- 應對策略：探測 (Probe) -> 分析(Analyze) -> 回應(Respond)
- 一個無序的情境, 需要跟環境作互動, 找出比較好的解決方式, 因果關係不明顯, 需要做實驗, 尋找比較好的做法
- 管理方式: 啟發型約束 (Enabling Constraint)
  - 沒有因果關係, 要跟情境/環境做互動，取得一些線索，否則沒有因果關係可循。需要建立 __允許失敗的環境__，並且儘可能嘗試多種可能，最好可以"平行進行實驗"。

#### 混亂 Chaotic

- 應對策略：行動(Act) -> 感知(Sense) ->回應(Respond)
- 管理方式：無, 立刻採取行動，再根據情況進行回應

### 需求的分層處理

軟體的需求可能來自多個地方, 討論雜亂, 該
1. 如何比較有條理? 
2. 如何記錄? 
3. 如何加入到現有開發流程?

#### 軟體需求的表達方式

1. 自然語言: 口語, Use case, user story
2. 模型(Model): 圖表, 公式, 程式碼

- 根據專案需求選擇適合的表達方式
 
#### 軟體需求的層次

- 範圍很廣, 需要分層
- 分層的重點在於根據提出需求的「出發點」來進行分層，並區分需求是
  1. 問題導向 (Problem-oriented) 還是
  2. 解法導向 (Solution-oriented)
- 先從問題導向再往下解法導向, 並確保大家是在同一個階層討論


- 各層級的需求來源/分類
    1. 商業流程層 (Business Process Layer)
        - stakeholder 利害關係人
        - business process 商業流程
        - external system 外部系統
    2. 使用流程層 (Usage Process Layer)
        - use case
        - quality
        - system constraint
    3. 系統流程層 (System Process Layer)
        - 軟體架構
        - 硬體需求

### 工具介紹 Google Jamboard

- [Jamboard](https://jamboard.google.com/)

1. 發想: 可以怎麼做? 用便利貼紀錄
  - 嚴禁批判
  - 自由發想
  - 不要離題
  - 以量取勝
2. 分類
  - 看哪些需求屬於同一類
3. 分層
  - 問題導向/解法導向

### 設計的分層處理 

#### 設計問題的產生因子 (Generators of design problems)

- 提出需求的人

1. 立法者 Legislator
2. 使用者 User: 真正使用產品的人
3. 客戶 Client: 對產品有熱情/資金, 但又需要其他專業人士協助的人
4. 設計師 Designer

#### 設計問題的階層

- 風險大 -> 小: 立法者 > 使用者 > 客戶 > 設計師
- 彈性大 -> 小: 設計師 > 客戶 > 使用者 > 立法者

- Uncle Bob 的 Clean Architectur
  - Business Rule, Entity
  - Use Case
  - Adapter 
  - Technique

### 技術風險

- 越接近"系統流程層"的需求, 那跟"軟體架構"的關係就比較大

