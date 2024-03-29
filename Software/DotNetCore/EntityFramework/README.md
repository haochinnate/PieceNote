
### References

* [Entity Framework Best Practices - Should EFCore Be Your Data Access of Choice?](https://www.youtube.com/watch?v=qkJ9keBmQWo)

### 建立web app project

1. 建立 ASP.NET Core Web Application
2. Project Name: EFDemoWeb
3. Solution Name: EFDemoApp
4. 選擇一般的 .NET Core -> ASP.NET Core 3.1 -> Web Application
5. 執行後, 會跳出網頁 

### 建立 class library

1. 建立新 project, 選擇 "Class Library (.NET Standard)" (不是 .NET Core, 也不是 .NET Framework)
2. Project Name: EFDataAccessLibrary
3. 砍掉預設建立的 Class1.cs
4. 建立 Models 資料夾
5. 在 Models 底下, 建立 Address, Email, Person 類別, 並分別加入一些 properties
6. 在 EFDataAccessLibrary 專案按右鍵, 選擇"Manage Nuget Packages..."
7. 安裝 Microsoft.EntityFrameworkCore.SqlServer package
8. 建立 DataAccess 資料夾
9. 在 DataAccess 底下, 建立 PeopleContext 類別, 繼承 DbContext

```csharp

    public class PeopleContext : DbContext
    {
        public PeopleContext(DbContextOptions options) : base(options) { }

        // three tables
        public DbSet<Person> People { get; set; }
        public DbSet<Address> Addresses { get; set; }
        public DbSet<Email> EmailAddresses { get; set; }
    }

```

10. 在 EFDemoWeb 專案 Dependencies, 按右鍵 Add Reference, 選擇 EFDataAccessLibrary 專案
11. EFDemoWeb project\Setup.cs\ConfigureService(...) 裡面增加 DbContext

```csharp

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            // adding our DB context to our dependency injection system
            services.AddDbContext<PeopleContext>(options =>
            {
                // using SQL server, and connection string is from appsettings.json
                options.UseSqlServer(Configuration.GetConnectionString("Default"));
            });
            services.AddRazorPages();
        }

```

12. 編輯 appsettins.json, 增加 ConnectionStrings
13. 在 "SQL Server Object Explorer" 中, 如果已經有db, 可以從屬性裡面看 "連接字串" (ConnectionString) 

```json
{
    "ConnectionStrings": {
        "Default": "Data Source=(localdb)...;Initial Catalog=EFDemoDB;Integrated Security=True;"
    }
}
```

### Create migration scripts

1. 打開 Package Manager Console(套件管理器主控台)
2. 輸入 "Add-Migration InitialDBCreation", 會有錯誤, 因為還沒有加 tooling
3. 在 EFDemoWeb project 中, Dependecies 按右鍵, 選擇 "Manage NuGet Packages..."
4. 安裝 "Microsoft.EntityFrameworkCore.Tools"
5. 再輸入一次 "Add-Migration InitialDBCreation", 會有紅字, 要將預設專案改成 EFDataAccessLibrary, 再跑一次
6. Migration 的code是根據我們建立的PeopleContext class 自動產生的
7. Up migration: allows you to go from where we're at to where wants to take us
8. Down migration: rollback, undo what you did
9. Person class 中有 List<Address>, 所以Addresses table 有一欄 PersonId, 但預設是 nullable, EmailAddresses table 也有相同問題

```csharp
     columns: table => new
     {
        Id = table.Column<int>(nullable: false)
            .Annotation("SqlServer:Identity", "1, 1"),
        StreetAddress = table.Column<string>(nullable: true),
        City = table.Column<string>(nullable: true),
        State = table.Column<string>(nullable: true),
        ZipCode = table.Column<string>(nullable: true),
        PersonId = table.Column<int>(nullable: true)
    }
```

10. 在Person 中, 增加一個 property, 再增加一個migrations: "Add-Migration AddAgeColumn"
11. PeopleContextModelSnapshot 類別 nvarchar(max), Unicode variable length character field, two bytes per character, 一般是 1~4000多個 bytes, nvarchar(max)可以放 2G? 8060 bytes 是 SQL 限制? 如果過長, 會存在disk, 而非DB.
　　  
* 如果有一些資料很常被query, 會另外create index, 但 non-clustered index 有限制:1700 bytes,  nvarchar(max) 超過很多, 所以不能在這上面用 index, 所以可能有 optimization 問題, 不能從columns 建立 lookups?
* varchar 和 nvarchar columns are assumed to be half full, [nvarchar performance](https://www.sqlservercentral.com/forums/topic/nvarchar4000-and-performance)

12. By default, Entity Framework does not create the ideal table design for U, 因為在宣告property 的時候, 型別是 string, 而且沒有設定 limitation, 所以是 nvarchar(max)

13. One-To-Many relationship

```csharp     
modelBuilder.Entity("EFDataAccessLibrary.Models.Address", b =>
    {
        b.HasOne("EFDataAccessLibrary.Models.Person", null)
        .WithMany("Addresses")
        .HasForeignKey("PersonId");
    });
```

### Create Database

1. 打開 Package Manager Console(套件管理器主控台), Default Project 選擇 EFDataAceessLibrary

2. 輸入 "Update-database", 會根據 Startup 類別的內容建立資料庫(appsettings.json 的 Default)

```cmd
Update-Database
```

3. 在 "SQLServer Object Explorer" 視窗底下就可以看到新建立的 EFDemoDB, 裡面已有四個 tables 

4. 接下來要修改 Model 的部分, 加入 DataAnnotations, 讓 EF 不要使用 nvarchar(max)

```csharp
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

// data annotation example
[Required]
[MaxLength(200)]
[MaxLength(10)]
[Column(TypeName = "varchar(10)")]

```

5. 每個 model 加完 data annotation 後, 回到 Package Manager Console, 增加新的 migrations

```cmd
Add-Migration AddedValidation
```

6. 修改之前, 要小心這個 schema 是不是會造成資料遺失, 再執行一次 update-database

```cmd
Update-Database
```

### Use Database

1. 在 EFDemoWeb\Pages\Index.cshtml.cs 中, 加入 import data 的 code

2. 使用json file 產生器來產生一些資料 generated.json

3. 建一個 function 來讀取, 只有當 database 沒資料的時候才 call?

```csharp
using System.Text.Json;


```

4. IndexModel 的 constructor 中, 增加 PeopleContext 參數, 因為在Startup 的 ConfigureServices 有用AddDbContext 做 DI 輸入, 所以會自動帶入

```csharp
public IndexModel(ILogger<IndexModel> logger, PeopleContext db)
{
    _logger = logger;
    _db = db;
}
```

5. 打開 SQL Server Management Studio (SSMS), 因為要 monitor DB. 在XEvent Profiler\Standard 設定 要聽的 sql server event, 來看 EF 對 database 做了什麼事情.

```sql
select * from dbo.People
```

6. EF C# Code(LoadSample function) 和 實際 SQL command 對應

```sql
/* _db.People.Count() */
select COUNT(*) from [People] AS [p]

/* */
insert 0 TABLE ([Id] int, [_Position] [int]);
MERGE [People]
```

7. SSMS 中 monitor 到的 command 上面按右鍵, 選擇 "Copy", 然後在文字編輯器上可以看到一堆 sql command 

8. EF 沒有建立 i store procefure for it, 一般會建立 store procedure 來處理insert 一堆資料. 而且不應該使用 "sp_executesql", DANGER!!, 會讓 app 有很多權限可以控制DB?

9. load People Table, including Address & Email

```csharp

var people = _db.People
    .Include(a => a.Addresses)
    .Include(e => e.EmailsAddresses)
    .ToList();

```

```sql
/* 對應 sql command */

/* duration 89533*/
/* logical reads 331 */
/* row count 1204: # of records that returns to our EF */
-- 100 筆資料 但是 row count 是 1204, 因為


SELECT [p].[Id], [p].[Age], [p].[FirstName], [p].[LastName], 
    [a].[Id] [a].[City], [a].[PersonId], [a].[State], [a].[StreetAddress], [a].[ZipCode], 
    [e.Id], [e].[EmailAddress], [e].[PersonId]
FROM [People] AS [p] 
LEFT JOIN [Address] AS [a] ON [p].[Id] = [a].[PersonId]
LEFT JOIN [EmailAddress] AS [e] ON [p].[Id] = [e].[PersonId]
ORDER BY [p].[Id], [a].[Id], [e].[Id]

-- give me everything from the People table, and if you find matches in Address Table, then give those values

-- Person 對 Address 的關係是 One-To-Many, 當在Address 找到三個Address 都有相同 PersonId時, 會找到重複的 Person(duplicate records), 造成 row count 是 1204

-- C# 那邊沒有顯示是因為 會 eliminate duplicate 

```

10. 如果C#那邊不使用 Include, People 的 property 不會有 Addresses 和 EmailAddresses 的資料, 不會 load 進來

```csharp

var people = _db.People
    // .Include(a => a.Addresses)
    // .Include(e => e.EmailsAddresses)
    .ToList();

```

```sql
/* 對應 sql command */

/* row count 100: # of records that returns to our EF */

SELECT [p].[Id], [p].[Age], [p].[FirstName], [p].[LastName]
FROM [People] AS [p] 

```

11. filter command in WHERE 的處理方式會不同 , can be converted into TSQL? and run on SQL server

```csharp

// 範例1

// 這行在執行的時候會發生錯誤
var people = _db.People
    .Include(a => a.Addresses)
    .Include(e => e.EmailsAddresses)
    .Where(x => ApprovedAge(x.Age))
    .ToList();

// 要改成下面這樣
var people = _db.People
    .Include(a => a.Addresses)
    .Include(e => e.EmailsAddresses)
    .ToList()
    .Where(x => ApprovedAge(x.Age));
    
// 但是ToList 在前面 1.這個會先 download 所有資料(ex:100筆), 再來跑這行 code
// 造成效率比較差
.Where(x => ApprovedAge(x.Age)) 

// SQL command: row count 是 1200


private bool ApprovedAge(int age)
{
    return (age >= 18 && age <= 65);
}


```

```csharp

// 範例2
var people = _db.People
    .Include(a => a.Addresses)
    .Include(e => e.EmailsAddresses)
    .Where(x => x.Age >=18 && x.Age <=65)
    .ToList();

// SQL command: row count 是 673

// 2. 這樣比較節省時間, 由 db serve 去做 filter & query
// filter before download 
.Where(x => x.Age >=18 && x.Age <=65) 

```

### Benefit of Entity Framework Core

1. Faster development speed. But it may be slow down if you want to make sure it's performance
2. You don't have to know SQL. Actually not..., you have to learn SQL to optimize

### Benefits of Dapper

1. Faster in production
2. Easier to work with for SQL developer
3. Designed for loose coupling

