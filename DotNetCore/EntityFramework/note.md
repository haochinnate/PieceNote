
### References

* [Entity Framework Best Practices - Should EFCore Be Your Data Access of Choice?](https://www.youtube.com/watch?v=qkJ9keBmQWo)

### 建立專案

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

