## Create project and install packages 

1. 開啟visual studio
2. create new project, 選擇 "Console App(.NET Core)"
3. Project Name: ConsoleUI, Solution Name: BetterConsoleApp
4. 在 project底下有 "Dependencies", 按右鍵選擇 "Manage NuGet Packages..."
    * 安裝 Microsoft.Extensions.Hosting (to set up our hosting environment)
    * 安裝 Serilog.Extensions.Hosting (alternative to the built-in hosting or logging system)
    * 安裝 Serilog.Settings.Configuration (告訴 appsettings.json 設定 configuration)
    * 安裝 Serilog.Sinks.Console (the location you want to send your logs to)(另外還有 ColoredConsole or RollingFile 等等可以選擇)
    * dependency injection system 則是使用 .NET core 內建的
5. 在 .csproj 檔案裡面, <ItemGroup> <PackageReference> 指 nuget package, 如果建立了一個新的 project, 可以把這些 package 內容複製過去

## 新增 appsettings.json (連結在 ConsoleApp_appsettings.json)

1. 在project按右鍵, Add -> New Item... -> appsettings.json
2. 在這個json按右鍵選擇 Properties, "Copy to Output Directory" 可以選擇 "Copy always" 或是 "Copy if newer", 確保有最新版本的設定檔
3. 三個目標: 
    * To use dependency injection
    * To use Serilog
    * To use our settings
4. 從 hooking all of these up together
5. log 會希望馬上可以log, 甚至在設定 DI 之前, 或在其他動作之前
=> create a manual connection to appsettings.json

### Main function and BuildConfig function
```csharp

static void Main(string[] args)
{
    var builder = new ConfigurationBuilder();
    BuildConfig(builder);

    #region Serilog
    // manual using appsettings.json to setup Serilog
    // ReadFrom: get ready for configuration
    // Enrich.FromLogContext(): gonna add extra stuff to logging
    // WriteTo: set write to console
    Serilog.Log.Logger = new LoggerConfiguration()
        .ReadFrom.Configuration(builder.Build())
        .Enrich.FromLogContext()
        .WriteTo.Console()
        .CreateLogger();
    #endregion

    Log.Logger.Information("Application Starting");

    // Host come from "Microsoft.Extensions.Hosting"
    // configure all our services, 如同 ASP.NET Core 的 configure services section
    // configuring everything
    var host = Host.CreateDefaultBuilder()
        .ConfigureServices((context, services) => {
            // Transient 是指每次要使用的時候都給一個新的 instance
            // 這邊用 GreetingService, 也可以用 interface(如果有實作的話)
            // services.AddTransient<GreetingService>();
            services.AddTransient<IGreetingService, GreetingService>();
        })
        .UseSerilog()
        .Build();

    // call GreetingService to use dependency injection system
    // svc will be the type of IGreetingService
    var svc = ActivatorUtilities.CreateInstance<GreetingService>(host.Services);
    // var svc = ActivatorUtilities.CreateInstance<IGreetingService>(host.Services);

    svc.Run(); // Run in GreetingService

}


// IConfigurationBuilder come from "Microsoft.Extensions.Configuration"
static void BuildConfig(IConfigurationBuilder builder)
{
    // it's going to create or add to builder the ability to talk to appsettings.json
    // 只有一行也可以, 但是因為還有 development mode 或 production mode
    // 不只 讀 appsettings.json, 也讀appsettings.development.json 或是 appsettings.production.json, 可以 override appsettings.json
    // 增加環境變數可以 override appsettings.json 裡的設定 ex: connection string
    builder.SetBasePath(Directory.GetCurrentDirectory())
        .AddJsonFile("appsettins.json", optional: false, reloadedOnChange: true)
        .AddJsonFile($"appsettins.{Environment.GetEnvironmentVariable("ASPNETCORE_ENVIRONMENT") ?? "Production"}.json", optional: true)
        .AddEnvironmentVariables();
}

```

### GreetingService (the class using DI)

```csharp

public interface IGreetingService
{
    Run();
}

// 建立一個新類別, 用來處理configure, 而不要放在 main裡面
public class GreetingService : IGreetingService
{
    // you don't modify the _log & _config, just use them
    private readonly ILogger<GreetingService> _log;
    private readonly IConfiguration _config;

    public GreetingService(ILogger<GreetingService> log, IConfiguration config)
    {
        _log = log;
        _config = config;
    }

    public void Run()
    {
        // get the LoopTimes from configuration
        for (int = 0; i < _config.GetValue<int>("LoopTimes"); i++)
        {
            // Serilog 不只會記錄 下方的 text, 還會以 runNumber 為名另外記錄 i 的數值
            // 這樣 log 的時候比較好找
            _log.LogInformation("Run number {runNumber}", i);
        }
    }
}

```

### json 說明

* Serilog.MinimumLevel.Override 是設定哪個 namespace 的 message 要用什麼等級log

* 在執行的時候可以去改變 appsettings.json, 原本可能是 warning/error or higher, 在有問題的時候才變成 information or higher
