
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

### Create migration scripts and database

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
　　*　

