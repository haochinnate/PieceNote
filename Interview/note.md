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

* References:
   * [WHEN TO USE ABSTRACT CLASSES AND WHEN INTERFACES.](https://www.codementor.io/@vipinc/when-to-use-abstract-classes-and-when-interfaces-c-interview-questions-jtzll1sn7)

* 介面是否可繼承介面? 抽象類是否可實現(implements)介面? 抽象類是否可繼承實體類(concrete class)?
答：介面可以繼承介面。抽象類可以實現(implements)介面，抽象類是否可繼承實體類，但前提是實體類必須有明確的建構函式。

* Why Interface
   * You don't have default or shared code implementation
   * You want to share data contracts (web services, SOA)
   * You have different implementations for each interface implementer (IDbCommand has SqlCommand and OracleCommand which implement the interface in specific ways)
   * You want to support multiple inheritance.
   * the functionality you are creating will be useful across a wide range of disparate objects, interfaces are best suited for providing common functionality to unrelated classes.
   * When creating a standalone project which can be changed at will, use an interface in preference to an abstract class; because, it offers more design flexibility.
   * Use interfaces to introduce polymorphic behavior without subclassing and to model multiple inheritance—allowing a specific type to support numerous behaviors.
   * Use an interface to design a polymorphic hierarchy for value types.
   * Use an interface when an immutable contract is really intended.
   * A well-designed interface defines a very specific range of functionality. Split up interfaces that contain unrelated functionality.
   
* Why Abstract
   * You have default or shared code implementation
   * You want to minimize code duplication
   * You want to easily support versioning(multiple version): By updating the base class, all inheriting classes are automatically updated with the change.
   * When creating a class library which will be widely distributed or reused—especially to clients, use an abstract class in preference to an interface; because, it simplifies versioning. This is the practice used by the Microsoft team which developed the Base Class Library. (COM was designed around interfaces.)
   * Use an abstract class to define a common base class for a family of types.
   * Use an abstract class to provide default behavior.
   * Subclass only a base class in a hierarchy to which the class logically belongs.

### functional programming 

* 強調抽象概念, 與category theory有些相關

* "避免改變狀態", "避免可變的的資料", "純函式"



### imperative programming vs. declarative programming

* imperative paradigm (指令式程式設計): 程式碼具體表達需要做什麼來達到目標。描述該做什麼(how to do)以及流程控制(flow control)

* declarative paradigm(宣告式程式設計): 藉由自然語言直觀的理解該行程式碼想要達到什麼樣子結果。描述在哪做什麼(what to do)以及資料流程(data flow)

