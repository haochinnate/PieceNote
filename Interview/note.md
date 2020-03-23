# Interview

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

## Stack vs. Heap
* References: 
   * [Stack and heap](https://dev.to/tyrrrz/interview-question-heap-vs-stack-c-5aae)
   * [C# Heap(ing) Vs Stack(ing) In .NET - Part One](https://www.c-sharpcorner.com/article/C-Sharp-heaping-vs-stacking-in-net-part-i/)

* C# 有兩個地方可以來存放object: stack, heap 

* Allocated 在 stack 中的物件只能在stack frame(execution of a method)裡面存取。 
* Aloocated 在 heap  中的物件可以在任何地方存取。
* 錯誤分類:  reference types 被分配在heap, 而 value types被分配在stack
* Reference types (classes, interfaces, delegates) 永遠被分配在heap
* 當把reference object 當作參數傳入或是 assign 到變數時, 是在傳送"參考"(reference)。參考(reference, 而非 referenced object)可以被分配在 stack 或是 heap上。
* 每一次物件被當作reference傳遞時, reference本身會被複製, 代表你可以改變reference 讓他指到不同物件. 就不會影響到前一個物件.
* Value types (derived from System.ValueType, e.g. int, bool, char, enum and any struct), 可以被分配在heap 或 stack上. 取決於他們是在哪裡被宣告的。
    * 如果是當作 method裡的變數, 那就是存在 stack 裡面。
	* 如果是當作 method 的參數, 那就是存在 stack 裡面。
	* 如果是class的 member, 那就是存在 heap 裡面, 跟隨他的parent。
	* 如果是struct的 member, 那就是存在 heap 裡面, 跟隨他的parent。
	
* While the objects stored on the stack are gone when the containing stack frame is popped, memory used by objects stored on the heap needs to be freed up by the garbage collector.  
* The Stack is more or less responsible for keeping track of what's executing in our code (or what's been "called").
* The Heap is more or less responsible for keeping track of our objects (our data, well... most of it - we'll get to that later.).  
* The Stack is self-maintaining, meaning that it basically takes care of its own memory management. When the top box is no longer used, it's thrown out.  
* The Heap, on the other hand, has to worry about Garbage collection (GC) - which deals with how to keep the Heap clean (no one wants dirty laundry laying around... it stinks!).
