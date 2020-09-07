# Dependency Inversion Principle

## Principle states:

* High-level modules should not depend on low-level modules. Both should depend on abstraction (e.g. interfaces)

* Abstractions should not depend on details. Details (concrete implementations) should depend on abstractions.

* Dependency Injection is one of the ways you make the principle work

## Bad Example 

*  呼叫的部分, 一般的寫法, 違反了 DI 

* Program Main 會 呼叫 Person 和 Chore 類別, 所以有依賴於這兩個類別, 屬於 high-level

* Chore 類別 也是算 high-level module, 因為它會呼叫 Logger, Emailer類別

* Logger, Emailer 是屬於 low-level module

* 當修改 low-level 類別時, 會影響 Chore, Program 類別

* 所以要改成 abstraction (interface)

```csharp
private void RegularExample()
{
    Person owner = new Person
    {
        FirstName = "Tim",
        LastName = "Corey",
        EmailAddress = "tim@iamtimcorey.com",
        PhoneNumber = "555-1212"
    };

    Chore chore = new Chore
    {
        ChoreName = "Take out the trash",
        Owner = owner
    };

    chore.PerformedWork(3);
    chore.PerformedWork(1.5);
    chore.CompleteChore();
}
```

* Chore 類別

```csharp
public class Chore
{
    public string ChoreName { get; set; }
    public Person Owner { get; set; }
    public double HoursWorked { get; set; }
    public bool IsComplete { get; set; }

    public void PerformedWork(double hours)
    {
        HoursWorked += hours;
        Logger log = new Logger();
        log.log($"Performed work on { ChoreName }");
    }

    public void CompleteChore()
    {
        IsComplete = true;
        
        Logger log = new Logger();
        log.log($"Completed { ChoreName }");
        
        Emailer emailer = new Emailer();
        emailer.SendEmail(Owner, $"The chore { ChoreName } is complete.");
    }
}
```

* Emailer 類別

```csharp
public class Emailer
{
    public void SendEmail(Person person, string message)
    {
        Console.WriteLine($"Simulating sending an email to { person.EmailAddress }");
    }
}
```

## 修改之後

* Person 類別 修改項目
    1. 擷取介面 IPerson

```csharp
// Person -> IPerson
public interface IPerson
{
    string EmailAddress { get; set; }
    string FirstName { get; set; }
    string LastName { get; set; }
    string PhoneNumber { get; set; }
}
```

* Program Main 修改項目
    1. Person 類別 改為 IPerson 介面
    2. 建立一個新類別 Factory, 負責涵蓋所有的 dependencies
    3. 把 Program Main 裡面, 建立 concrete class 物件的部分替換掉 ex: new Person, new Chore
    4. Chore 類別 改為 IChore 介面

```csharp
private void RegularExample()
{
    IPerson owner = Factory.CreatePerson();

    owner.irstName = "Tim";
    owner.LastName = "Corey";
    owner.EmailAddress = "tim@iamtimcorey.com";
    owner.PhoneNumber = "555-1212";

    IChore chore = Factory.CreateChore();
    
    chore.ChoreName = "Take out the trash";
    chore.Owner = owner;

    chore.PerformedWork(3);
    chore.PerformedWork(1.5);
    chore.CompleteChore();
}

```

```csharp
// its job is going to be is to new up instances when needed
// one place that has all the dependencies 
public static class Factory
{
    public static IPerson CreatePerson()
    {
        return new Person();
    }

    public static IChore CreateChore()
    {
        return new Chore(CreateLogger(), CreateMessageSender());
    }

    public static ILogger CreateLogger()
    {
        return new Logger();
    }

    public static IMessageSender CreateMessageSender()
    {
        return new Emailer();
    }
}

```


* Chore 類別 修改項目 
    1. 改為使用 IPerson介面
    2. 擷取介面 IChore
    3. Chore 類別新增一個 constructor, 把ILogger 和 IMessageSender 傳進來
    4. 傳進來 存在一個 private field
    5. 將 function 內 原先的 Logger, 和 Emailer 換掉

```csharp

public interface IChore
{
    string ChoreName { get; set; }
    IPerson Owner { get; set; }
    double HoursWorked { get; set; }
    bool IsComplete { get; set; }

    void PerformedWork(double hours);
    void CompleteChore();
}

public class Chore : IChore
{
    private ILogger _logger;
    private IMessageSender _messageSender;

    public string ChoreName { get; set; }
    public IPerson Owner { get; set; }
    public double HoursWorked { get; set; }
    public bool IsComplete { get; set; }

    public Chore(ILogger logger, IMessageSender messageSender)
    {
        _logger = logger;
        _messageSender = messageSender;
    }

    public void PerformedWork(double hours)
    {
        HoursWorked += hours;
        // Logger log = new Logger();
        _logger.log($"Performed work on { ChoreName }");
    }

    public void CompleteChore()
    {
        IsComplete = true;
        
        // Logger log = new Logger();
        _logger.log($"Completed { ChoreName }");
        
        // Emailer emailer = new Emailer();
        // emailer.SendEmail(Owner, $"The chore { ChoreName } is complete.");
        _messageSender.SendMessage(Owner, $"The chore { ChoreName } is complete.");
    }
}
```

* Emailer 類別 修改項目
    1. 改為使用 IPerson介面
    2. 擷取介面 IMessageSender

```csharp

public interface IMessageSender
{
    void SendMessage(IPerson person, string message);
}

public class Emailer : IMessageSender
{
    public void SendMessage(IPerson person, string message)
    {
        Console.WriteLine($"Simulating sending an email to { person.EmailAddress }");
    }
}

```

* Logger 類別 修改項目
    1. 擷取介面 IMessageSender

```csharp
public interface ILogger
{
    void Log(string message);
}

public class Logger : ILogger
{
    public void Log(string message)
    {
        Console.WriteLine($"");
    }
}
```

* 修改之後, 相依關係都是在 Factory那邊, Program Main 只相依於 Factory

* 建立一個新類別 Texter, 直接替換掉 Emailer

```csharp

public class Texter : IMessageSender
{
    public void SendMessage(IPerson person, string message)
    {
        Console.WriteLine($"I am texting { person.FirstName } to say { person.message }");
    }
}

// 可以直接在 Factory 的  CreateMessageSender function 那邊改成
public static IMessageSender CreateMessageSender()
{
    return new Texter();
}
```

* 因為沒有直接相依 directly dependecies, 只有相依於 abstractions, not the implementation

* SOLID takes us as a whole, it takes us into having lots of really tiny little parts, things that do only one thing, things that don't have dependencies, things that are just self-contained tiny and against an interface

* So we can unplug and plug in something new without problem
