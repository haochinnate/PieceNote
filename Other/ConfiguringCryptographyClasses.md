
# [Configuring Cryptography Classes](https://docs.microsoft.com/en-us/dotnet/framework/configure-apps/configure-cryptography-classes)

**Describe how to map an algorithm name to a cryptography class and an object identifier to a cryptography algorithm**

* Windows的SDK允許 computer administrators to configure the default cryptographic algorithms and algorithm implementations that the .NET Framework and appropriately written applications use.
* 如果一家公司有自己實作的cryptographic algorithm, 可以把這個實作變成預設使用, 取代Windows SDK裡面的實作.
* Although managed applications that use cryptography can always choose to explicitly bind to a particular implementation, it is recommended that they create cryptographic objects by using the crypto configuration system.

## In This Section

### [Mapping Algorithm Names to Cryptography Classes](https://docs.microsoft.com/en-us/dotnet/framework/configure-apps/map-algorithm-names-to-cryptography-classes)
**描述如何用 algorithm name 去對應到 cryptography class**

利用Windows SDK, 開發人員有4種方式可以建立 cryptography object
1. 用 **new** operator 來建立 object
2. 呼叫該演算法 abstract class 的 **Create** 方法, 來建立有實作特定 cryptography algorithm 的 object
3. 呼叫 [CryptoConfig.CreateFromName](https://docs.microsoft.com/en-us/dotnet/api/system.security.cryptography.cryptoconfig.createfromname?view=netframework-4.7)方法, 來建立有實作特定 cryptography algorithm 的 object
4. 呼叫該類型的演算法(例如 [SymmetricAlgorithm](https://docs.microsoft.com/en-us/dotnet/api/system.security.cryptography.symmetricalgorithm))abstract class 的**Create** 方法, 來建立實作 a class of cryptographic algorithms (例如 symmetric block cipher)的物件

例如, 假設開發人員想要 compute the SHA1 hash of a set of bytes.

[System.Security.Cryptography](https://docs.microsoft.com/en-us/dotnet/api/system.security.cryptography) 這個 namespace 包含了兩種 SHA1 演算法的實作方式(其一是 purely managed implemenration, 另一個是 wraps CryptoAPI)。

開發人員可以藉由 **new** operator 來選擇特定的SHA1 實作方式(例如 SHA1Managed).

~~~~~
byte[] data = new byte[DATA_SIZE];
byte[] result;
SHA1 shaM = new SHA1Managed();
result = shaM.ComputeHash(data);
~~~~~

但是如果不在意common language runtime載入了哪一個class，只要該clsss是實作SHA1 hash 演算法, 那開發人員可以藉由 [SHA1.Create](https://docs.microsoft.com/en-us/dotnet/api/system.security.cryptography.sha1.create?view=netframework-4.7)方法來建立物件。
這個方法叫做 **System.Security.Cryptography.CryptoConfig.CreateFromName("System.Security.Cryptography.SHA1")** 它一定要回傳SHA1 hash演算法的實作。


開發人員也可以呼叫 **System.Security.Cryptography.CryptoConfig.CreateFromName("SHA1")**, 因為 cryptography configuration 預設有包含 .NET Framework 包含的演算法的 short names。

如果開發人員不在乎要使用哪一個 hash algorithm, 那可以呼叫 [HashAlgorithm.Create](https://docs.microsoft.com/en-us/dotnet/api/system.security.cryptography.hashalgorithm.create?view=netframework-4.7)方法, 它會回傳實作hashing transformation的物件


#### Mapping Algorithm Names in Configuration Files

根據預設, 4種情況都會回傳 [SHA1CryptoServiceProvider](https://docs.microsoft.com/en-us/dotnet/api/system.security.cryptography.sha1cryptoserviceprovider?view=netframework-4.7)的物件。
但是 machine administrator 可以改變後面兩個情況的 method 要回傳的object 型別。要達成這個目標，你要在machine configuration file(**Machine.config**)中建立friendly algorithm name 與 你想要使用的 class 之間的對應。

Machine.config 放在 %windir%\Microsoft.NET\Framework64\[version]\config\machine.config 裡面

以下的範例展示了如何設定在 runtime 時, 讓以下三個方法回傳自己建立的 MySHA1HashClass 物件。 
* **System.Security.Cryptography.SHA1.Create**
* **System.Security.CryptoConfig.CreateFromName("SHA1")** 
* **System.Security.Cryptography.HashAlgorithm.Create** 

~~~~~
<configuration>  
   <!-- Other configuration settings. -->  
   <mscorlib>  
      <cryptographySettings>  
         <cryptoNameMapping>  
            <cryptoClasses>  
               <cryptoClass MySHA1Hash="MySHA1HashClass, MyAssembly  
                  Culture='en', PublicKeyToken=a5d015c7d5a0b012,  
                  Version=1.0.0.0"/>  
            </cryptoClasses>  
            <nameEntry name="SHA1" class="MySHA1Hash"/>  
            <nameEntry name="System.Security.Cryptography.SHA1"  
                       class="MySHA1Hash"/>  
            <nameEntry name="System.Security.Cryptography.HashAlgorithm"  
                       class="MySHA1Hash"/>  
         </cryptoNameMapping>  
      </cryptographySettings>  
   </mscorlib>  
</configuration>
~~~~~

你可以對 element 中的 attribute 命名(例如 attribute MySHA1Hash)。Common language runtime 利用 **\<cryptoClass\>** element 的 attribute 的值作為字串來尋找 class。你可以使用任何滿足在[Specifying Fully Qualified Type Names](https://docs.microsoft.com/en-us/dotnet/framework/reflection-and-codedom/specifying-fully-qualified-type-names)中要求的字串。


多個演算法名稱都可以對應到相同的類別。**\<nameEntry\>** element 會將類別對應到一個friendly algorithm name。 **name** attribute 可以是
呼叫 **System.Security.Cryptography.CryptoConfig.CreateFromName** 方法時要使用的字串 或是 **System.Security.Cryptography** namespace 裡面 abstract cryptography class 的名稱. **class** attribute 的值為 **\<cryptoClass\>** element 中 attribute 的名稱.


For a list of default names and the classes they map to, see [CryptoConfig](https://docs.microsoft.com/en-us/dotnet/api/system.security.cryptography.cryptoconfig).

### [Mapping Object Identifiers to Cryptography Algorithms](https://docs.microsoft.com/en-us/dotnet/framework/configure-apps/map-object-identifiers-to-cryptography-algorithms)
**描述如何用 object identifier 去對應到 cryptography algorithm**


## Related Sections 
### [Cryptographic Services](https://docs.microsoft.com/en-us/dotnet/standard/security/cryptographic-services)
**提供了 Windows SDK 支援的 cryptographic services 概觀**  

### [Cryptography Setting Schema](https://docs.microsoft.com/en-us/dotnet/framework/configure-apps/file-schema/cryptography/index)
**Describes elements that map friendly algorithm names to classes that implemnt cryptography algorithms**  

### [Caspol.exe (Code Access Security Policy Tool)](https://docs.microsoft.com/en-us/dotnet/framework/tools/caspol-exe-code-access-security-policy-tool)
  
