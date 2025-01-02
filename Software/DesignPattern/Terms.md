# Terms

## 物件導向術語回顧

### 抽象類別(abstract class) 

- 定義了一組相關類別的行為 
- 定義了概念上相似的一組類別的方法和公共屬性。抽象類別不能實體化

### 類別(class) 

- 根據物件所具有的責任定義物件的類型。責任可以分為行為和/或狀態。這些分別是由方法 和/或資料實作的
- 物件的藍圖—為其類型的物件定義方法和資料

#### 具體類別(Concrete class) 

- 實作抽象類別某一特定類型行為的類別。 具體類別是一個概念特定、不變的實作

#### 衍生類別

- 從基礎類別特殊化的類別,包含基礎類別所有的屬性和方法,但還可能包含其他屬性或不同的方法實作


#### 超類別

- 其他的類別從中衍生的類別,包含所有衍生類別都要使用的主要資料和方法的定義 (方法可能改寫)

#### 屬性

- 與物件關聯的資料(也稱為資料成員,datamember)

#### 成員

- 類別的資料或方法

#### 方法 

- 與物件關聯的副程式

#### 建構函數

- 在建立物件時呼叫的特殊方法

#### 解構函數

- 在銷毀物件時呼叫的特殊方法

### 封裝(encapsulation) 

- 通常定義為資料隱藏, ,但最好將它看作任何形式的隱藏(類型、實作和設計等等)
- 任何形式的隱藏。物件封裝其資料, 抽象類別封裝其衍生的具體類別。

### 繼承(inheritance) 

- 一個類別繼承另一個類別,是指它接受了該類別的一些或者所有性質。
- 起始類別稱為基礎類別、超類別、父類別或者一般類別
- 而繼承類別稱為衍生類別、子類別或者特殊化類別 
- 一種特殊化類別的方式,用於將衍生類別與其基礎類別聯繫起來

### 實體(instance) 

- 類別的特例(總是一個物件)。類別的特殊實體或者實體。每個物件都有自己的狀態。因此同一個類型(類別)可以有多個物件
- 類別的特定物件

#### 實體化(instantiation) 

- 建立類別的一個實體的過程

### 物件

- 具有責任的實體。一個特殊的、自成一體的容器,包含資料和處理資料的方法。
- 物件的資料對於外部物件是受保護的。

### 介面(interface) 

- 介面與類別類似,但是只為其成員提供規約而不提供實作。
- 它與只含有抽象成員的抽象類別很相似。程式設計的時候,如果需要幾個類別共用公共基礎類別中沒有一些特性,而且希望確保每個類別自己實作這些特性(因為所有成員都是抽象的),就應該使用介面。

### 視角(perspective) 

- 觀察物件有三種視角:概念視角、規約視角和實作視角。
- 這三個不同層次的差別在理解抽象類別與其衍生類別之間的關係上用處很大。
- 抽象類別定義了如何在概念層次上解決問題,還提供了與任何衍生物件通訊的規約。
- 每個衍生類別都依需要提供特定的實作 


### 多型(polymorphism)

- 能夠用一種方式參照一個類別的不同衍生類別, 但獲得的行為對應於參照的衍生類別 
- 相關的物件根據其具體類型實作方法的能力

### 功能分解

- 一種分析方法,將問題逐步分解成小的功能