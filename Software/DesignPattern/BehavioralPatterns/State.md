# State

## 意圖

- State 是一種行為設計模式，允許object在其內部狀態發生變化時改變其行為。它看起來就像該object改變了其類別一樣。
- State 模式建議為物件的所有可能狀態創建新的類別，並將所有與狀態相關的行為提取到這些類別中。

## 使用時機/應用場合

1. 當你有一個物件的行為會根據當前狀態而改變，且狀態數量龐大且與狀態相關的程式碼經常變更時，可以使用 State pattern。  
  - 該模式建議將所有與狀態相關的程式碼提取到一組獨立的類別中。
  - 這樣，你可以獨立地新增新狀態或更改現有狀態，而不會影響其他狀態，從而降低維護成本。  

2. 當你的類別充滿大量的條件判斷語句，這些條件根據類別內的欄位值來決定行為時，可以使用 State pattern。  
  - State pattern 允許你將這些條件分支提取到對應的 state class 方法中。
  - 這樣做的同時，你還可以清理主類別中的臨時欄位和與狀態相關的輔助方法，使程式碼更加整潔。  

3. 當你在基於條件的狀態機(state machine)中，發現不同狀態之間存在大量重複的程式碼時，可以使用 State pattern。  
  - State pattern 允許你組合 狀態類別的繼承層次，並透過將共用程式碼提取到抽象基類中來減少重複程式碼。

## 與其他模式的關係

- [參考](../StructuralPatterns/Adapter.md#adapter-vs-bridgestatestrategy)

Bridge、State、Strategy（以及在某種程度上 Adapter）這些模式在結構上非常相似。事實上，它們都基於 **組合（Composition）**，即將工作委派給其他物件。然而，它們解決的是不同的問題。設計模式不僅僅是一種特定的程式碼結構方案，它還能向其他開發人員傳達該模式所解決的問題。  

**State 模式** 可以被視為 **Strategy 模式** 的擴展。這兩種模式都基於 **組合**，透過將部分工作委派給輔助物件來改變 **Context** 的行為。  

然而，**Strategy 模式** 讓這些物件彼此完全獨立且互不知曉，而 **State 模式** 則不會限制具體狀態之間的相互依賴，允許它們隨時改變 **Context** 的狀態。

Bridge, State, Strategy (and to some degree Adapter) have very similar structures. Indeed, all of these patterns are based on composition, which is delegating work to other objects. However, they all solve different problems. A pattern isn’t just a recipe for structuring your code in a specific way. It can also communicate to other developers the problem the pattern solves.

State can be considered as an extension of Strategy. Both patterns are based on composition: they change the behavior of the context by delegating some work to helper objects. Strategy makes these objects completely independent and unaware of each other. However, State doesn’t restrict dependencies between concrete states, letting them alter the state of the context at will.

## Code Example From Guru

- [source code links]()

```csharp

```

### 成員介紹/說明

#### Context

- 儲存對某個具體state物件的reference，並將所有與狀態相關的工作委託給該物件。
- Context 透過 State 介面 與狀態物件進行通信，並提供一個 setter 方法來傳入新的狀態物件。  

#### State 介面

- 宣告了與狀態相關的方法。這些方法應該對所有具體狀態都適用，因為你不希望某些狀態擁有永遠不會被調用的無用方法。  


#### ConcreteStates 類別


- 具體狀態為狀態相關的方法提供自己的實作。為了避免在多個狀態之間重複相似的程式碼，可以使用中介的抽象類別(intermediate abstract classes)來封裝一些通用行為。  

- 狀態object 可能會儲存一個指向 __Context__ 物件的反向引用。
- 透過這個引用，狀態可以從 Context 物件獲取所需的資訊，並且可以觸發狀態轉換。  

#### Trainsition

- __Context__ 和 __具體狀態__ 都可以設定 Context 的下一個狀態，並透過替換 Context 內部的狀態物件來執行實際的狀態轉換。


## UML 圖

![Pattern](../resources/UML_.svg)


```

```