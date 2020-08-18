
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


