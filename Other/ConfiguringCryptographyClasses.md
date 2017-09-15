
# [Configuring Cryptography Classes](https://docs.microsoft.com/en-us/dotnet/framework/configure-apps/configure-cryptography-classes)

**Describe how to map an algorithm name to a cryptography class and an object identifier to a cryptography algorithm**

* Windows的SDK允許 computer administrators to configure the default cryptographic algorithms and algorithm implementations that the .NET Framework and appropriately written applications use.
* 如果一家公司有自己實作的cryptographic algorithm, 可以把這個實作變成預設使用, 取代Windows SDK裡面的實作.
* Although managed applications that use cryptography can always choose to explicitly bind to a particular implementation, it is recommended that they create cryptographic objects by using the crypto configuration system.

## In This Section

### [Mapping Algorithm Names to Cryptography Classes](https://docs.microsoft.com/en-us/dotnet/framework/configure-apps/map-algorithm-names-to-cryptography-classes)
**描述如何用 algorithm name 去對應到 cryptography class**

### [Mapping Object Identifiers to Cryptography Algorithms](https://docs.microsoft.com/en-us/dotnet/framework/configure-apps/map-object-identifiers-to-cryptography-algorithms)
**描述如何用 object identifier 去對應到 cryptography algorithm**


## Related Sections 
### [Cryptographic Services](https://docs.microsoft.com/en-us/dotnet/standard/security/cryptographic-services)
**提供了 Windows SDK 支援的 cryptographic services 概觀**  

### [Cryptography Setting Schema](https://docs.microsoft.com/en-us/dotnet/framework/configure-apps/file-schema/cryptography/index)
**Describes elements that map friendly algorithm names to classes that implemnt cryptography algorithms**  

### [Caspol.exe (Code Access Security Policy Tool)](https://docs.microsoft.com/en-us/dotnet/framework/tools/caspol-exe-code-access-security-policy-tool)
  
