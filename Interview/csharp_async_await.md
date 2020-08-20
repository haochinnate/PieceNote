
# C# async/await

* RunDownloadSync() -> RunDownloadAsync() -> RunDownloadParallelAsync()

## Sync

```csharp
private void RunDownloadSync()
{
    List<string> websites = PropData();

    foreach(string site in websites)
    {
        WebsiteDataModel results = DownloadWebsite(site);
        ReportWebsiteInfo(results);
    }
}
```

## Async

```csharp
private async void Caller()
{
    await RunDownloadAsync();
    await RunDownloadParallelAsync();
}

// don't return void from an asynchronous method, just return Task
// or return Task<string> Task<T>
private async Task RunDownloadAsync()
{
    List<string> websites = PropData();

    foreach(string site in websites)
    {
        // await: you need to run this asynchronously, but you need to wait for it's result
        WebsiteDataModel results = await Task.Run(() => {
            DownloadWebsite(site)
        });

        ReportWebsiteInfo(results);
    }
}

private async Task RunDownloadParallelAsync()
{
    List<string> websites = PropData();
    List<Task<WebsiteDataModel>> tasks = new List<Task<WebsiteDataModel>>();

    foreach(string site in websites)
    {
        // just store the task, not yet start running 
        tasks.Add(Task.Run(() => { DownloadWebsite(site)}));
    }

    // the type of results is WebsiteDataModel[]
    var results = await Task.WhenAll(tasks);

    // print the result here
    foreach(var item in results)
    {
        ReportWebsiteInfo(item);
    }
}
```

## common function for time consuming 

```csharp
private WebsiteDataModel DownloadWebsite(string websiteURL)
{
    WebsiteDataModel output = new WebsiteDataModel();
    WebClient client = new WebClient();

    output.WebsiteUrl = websiteURL;
    output.WebsiteData = client.DownloadString(websiteURL);

    // async Task<WebsiteDataModel>
    // output.WebsiteData = await client.DownloadStringAsync(websiteURL);

    return output;
}

private void ReportWebsiteInfo(WebsiteDataModel data)
{
    // output the data.WebsiteData and related information to UI
}
```