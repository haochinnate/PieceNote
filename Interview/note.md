### struct vs. class

* struct is value type, not reference type
    * 可以帶有方法、欄位、索引、屬性、運算子方法和事件；
    * 可定義建構函式，不能定義解構函式
    * 不能被繼承
    * 可以實現多個介面
    * 成員訪問描述符不能為： abstract，virtual，protected
    * 與class不同，介面例項化可以不適用 New

|   | struct  | class | 
|---|---|---|
| 型態 | value type | reference type |
| 記憶體 | stack | heap |
| 繼承 | only interface | inheritance and interface |
| Null | cannot be NULL | nullable |

### value type vs. reference type

* variable container a value type containers the __entire value type__
* copying the contents of a value type variable into another variable, __copies the entire contents__ into the new variable, __making the two distinct__. In other words, after the copy, changes to one won't affect the other

* variable container a reference type containers __a pointer or a reference to memory__
* copying the contents of a reference type variable into another variable, __copies the reference__, which means you now have two references to the same somewhere else storage of the actual data. In other words, after the copy, changing the data in one reference __will appear to affect__ the other as well, but only because you're really just looking at the same data both places


### class vs. interface 

* 介面是否可繼承介面? 抽象類是否可實現(implements)介面? 抽象類是否可繼承實體類(concrete class)?
答：介面可以繼承介面。抽象類可以實現(implements)介面，抽象類是否可繼承實體類，但前提是實體類必須有明確的建構函式。

### functional programming 

* 強調抽象概念, 與category theory有些相關

* "避免改變狀態", "避免可變的的資料", "純函式"



### imperative programming vs. declarative programming

* imperative paradigm (指令式程式設計): 程式碼具體表達需要做什麼來達到目標。描述該做什麼(how to do)以及流程控制(flow control)

* declarative paradigm(宣告式程式設計): 藉由自然語言直觀的理解該行程式碼想要達到什麼樣子結果。描述在哪做什麼(what to do)以及資料流程(data flow)

