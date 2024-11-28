# Facade

| 項目      | 描述 |
| -------- | ------- |
| 意圖 | 希望簡化原有系統的使用方式。 需要定義自己的介面。|
| 問題        | 只需要使用某個複雜系統的子集,或者,需要以一種特殊的方式與系統交流。 |
| 解決方案      | Facade為原有系統的客戶提供了一個新的介面。 | 
| 參與者和協作者 | 為客戶提供的一個簡化介面,使系統更容易使用。 及現有的各個子系統 |  
| 效果         | Facade模式簡化了對所需子系統的使用過程。但是,由於Facade並不完整 因此客戶可能無法使用某些功能。 | 
| 實作         | 1. 定義一個(或多個)具備所需介面的新類別 <br/> 2. 讓新的類別使用原有的系統 | 
| 一般性結構    |  |


## 意圖

- 為子系統中的一組介面定義一個統一介面。
- Facade 模式定義了一個更高層的介面，使子系統更加容易使用。
- 一個一致的高層介面

## 問題

- 只使用系統的一部分功能
- 或是以特殊方式與系統交流
- 多數工作還是需要由底層系統完成, Facade 提供了一組容易理解的方法

以下內容只是我用來紀錄而已, 你不用回應

## 使用時機/應用場合

  1. 當您需要對複雜的子系統提供一個有限但簡單的接口時，可以使用 Facade。

  2. 當您想將子系統分層結構化時，可以使用外觀模式。為子系統的每個層級創建 facade，並定義進入該層的入口點。

## 與其他模式的關係

### Facade vs. Adapter

- Facade 為現有物件定義了一個新介面，而 Adapter 則試圖使現有interface 變得可用。Adapter 通常只包裝一個物件，而 facade 則處理整個子系統的物件。

### Facade vs. Abstract Factory

- 當只想要隱藏子系統物件的創建方式，不想暴露給client code時，可以使用抽象工廠模式（Abstract Factory）作為外觀模式的替代方案。

### Facade vs. Flyweight

- 享元模式（Flyweight）展示了如何創建大量的小物件，而外觀模式則展示了如何創建一個單一物件, 此物件用來表示整個子系統。

### Facade vs. Mediator

- 外觀模式和中介者模式（Mediator）有類似的工作：它們試圖組織大量緊耦合類別之間的協作。
- 外觀模式為一個子系統對象定義了一個簡化的interface，但它不會引入任何新功能。子系統本身對外觀對象一無所知。子系統內的objects仍然可以直接通信。
- 中介者模式則集中管理系統組件之間的通信。這些組件只知道mediator object，而不會直接互相通信。

### Facade vs. Singleton

- 在大多數情況下，facade 類別可以轉變為單例模式(Singleton)，因為多數案例中, 通常一個facade object已經足夠。


### Facade vs. Proxy

- facade 和 proxy 有相似之處，兩者都用於緩衝一個複雜的實體並自行初始化它。但與外觀模式不同的是，代理模式的interface與其服務物件相同，這使得它們可以互換使用。



## Code Example From Guru

- [source code links](https://refactoring.guru/design-patterns/facade/csharp/example)

```csharp
using System;

namespace RefactoringGuru.DesignPatterns.Facade.Conceptual
{
    // The Facade class provides a simple interface to the complex logic of one
    // or several subsystems. The Facade delegates the client requests to the
    // appropriate objects within the subsystem. The Facade is also responsible
    // for managing their lifecycle. All of this shields the client from the
    // undesired complexity of the subsystem.
    public class Facade
    {
        protected Subsystem1 _subsystem1;
        
        protected Subsystem2 _subsystem2;

        public Facade(Subsystem1 subsystem1, Subsystem2 subsystem2)
        {
            this._subsystem1 = subsystem1;
            this._subsystem2 = subsystem2;
        }
        
        // The Facade's methods are convenient shortcuts to the sophisticated
        // functionality of the subsystems. However, clients get only to a
        // fraction of a subsystem's capabilities.
        public string Operation()
        {
            string result = "Facade initializes subsystems:\n";
            result += this._subsystem1.operation1();
            result += this._subsystem2.operation1();
            result += "Facade orders subsystems to perform the action:\n";
            result += this._subsystem1.operationN();
            result += this._subsystem2.operationZ();
            return result;
        }
    }
    
    // The Subsystem can accept requests either from the facade or client
    // directly. In any case, to the Subsystem, the Facade is yet another
    // client, and it's not a part of the Subsystem.
    public class Subsystem1
    {
        public string operation1()
        {
            return "Subsystem1: Ready!\n";
        }

        public string operationN()
        {
            return "Subsystem1: Go!\n";
        }
    }
    
    // Some facades can work with multiple subsystems at the same time.
    public class Subsystem2
    {
        public string operation1()
        {
            return "Subsystem2: Get ready!\n";
        }

        public string operationZ()
        {
            return "Subsystem2: Fire!\n";
        }
    }


    class Client
    {
        // The client code works with complex subsystems through a simple
        // interface provided by the Facade. When a facade manages the lifecycle
        // of the subsystem, the client might not even know about the existence
        // of the subsystem. This approach lets you keep the complexity under
        // control.
        public static void ClientCode(Facade facade)
        {
            Console.Write(facade.Operation());
        }
    }
    
    class Program
    {
        static void Main(string[] args)
        {
            // The client code may have some of the subsystem's objects already
            // created. In this case, it might be worthwhile to initialize the
            // Facade with these objects instead of letting the Facade create
            // new instances.
            Subsystem1 subsystem1 = new Subsystem1();
            Subsystem2 subsystem2 = new Subsystem2();
            Facade facade = new Facade(subsystem1, subsystem2);
            Client.ClientCode(facade);
        }
    }
}
```