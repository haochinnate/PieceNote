# Facade

| 項目      | 描述 |
| -------- | ------- |
| 意圖 | 希望簡化原有系統的使用方式。 需要定義自己的介面。|
| 問題        | 只需要使用某個複雜系統的子集,或者,需要以一種特殊的方式與系統交流。 |
| 解決方案      | Facade為原有系統的客戶提供了一個新的介面。 | 
| 參與者和協作者 | 為客戶提供的一個簡化介面,使系統更容易使用。 及現有的各個子系統 |  
| 效果         | Facade模式簡化了對所需子系統的使用過程。但是,由於Facade並不完整 因此客戶可能無法使用某些功能。 | 
| 實作         | 1. 定義一個(或多個)具備所需介面的新類別 <br/> 2.讓新的類別使用原有的系統 | 
| 一般性結構    |  |


## 意圖

- 為子系統中的一組介面定義一個統一介面。
- Facade 模式定義了一個更高層的介面，使子系統更加容易使用。
- 一個一致的高層介面

## 問題

- 只使用系統的一部分功能
- 或是以特殊方式與系統交流
- 多數工作還是需要由底層系統完成, Facade 提供了一組容易理解的方法

## Code Example From Guru

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