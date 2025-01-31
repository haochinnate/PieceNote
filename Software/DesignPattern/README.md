# Design Pattern

## References

- [Refactoring Guru](https://refactoring.guru/design-patterns)
- 設計模式的解析與活用 ISBN: 978-986-201-820-0
- [術語整理](./Terms.md)

## 模式的關鍵特徵

| 項目      | 描述 |
| -------- | ------- |
| 名稱  | 每個模式都有唯一的用於標識的名稱 |
| 意圖 | 模式的目的 |
| 問題/動機         | 模式要解決的問題 |
| 解決方案      | 模式怎樣為問題提供適合其所處環境的一個解決方案 | 
| 參與者和協作者 | 模式所涉及的實體 |  
| 效果         | 使用模式的效果,研究模式中發揮作用的各種因素 | 
| 實作         | 模式的實作方式(注意:實作只是模式的具體體現,而不能視為模式本身) | 
| 一般性結構    | 顯示模式典型結構的標準圖 |


## Creational patterns

- 不同的 object creation mechanisms

### 清單

- [Factory Method](CreationalPatterns/FactoryMethod.md)
- [Abstract Factory](CreationalPatterns/AbstractFactory.md), 複雜度: 2, 人氣: 3
- [Builder]() 
- [Prototype]()
- [Singleton](CreationalPatterns/Singleton.md), 複雜度: 1, 人氣: 2
- [Object Pool](CreationalPatterns/ObjectPool.md)

## Structural patterns

- 如何將物件,類別組合成更大的結構

### 清單

- [Adapter](StructuralPatterns/Adapter.md), 複雜度: 1, 人氣: 3
- [Bridge](StructuralPatterns/Bridge.md), 複雜度: 3, 人氣: 1
- [Composite](StructuralPatterns/Composite.md), 複雜度: 2, 人氣: 2
- [Decorator](StructuralPatterns/Decorator.md), 複雜度: 2, 人氣: 2
- [Facade](StructuralPatterns/Facade.md), 複雜度: 1, 人氣: 2
- [Flyweight]()
- [Proxy](StructuralPatterns/Proxy.md), 複雜度: 2, 人氣: 1

## Behavioral patterns

- 物件之間的演算法及權責分配

### 清單

- [Chain of Responsibility]()
- [Command](BehavioralPatterns/Command.md), 複雜度: 1, 人氣: 3
- [Iterator](BehavioralPatterns/Iterator.md), 複雜度: 2, 人氣: 3
- [Mediator]()
- [Memento]()
- [Observer](BehavioralPatterns/Observer.md), 複雜度: 2, 人氣: 3
- [State]()
- [Strategy](BehavioralPatterns/Strategy.md), 複雜度: 1, 人氣: 3
- [Template Method](BehavioralPatterns/TemplateMethod.md), 複雜度: 1, 人氣: 2
- [Visitor](BehavioralPatterns/Visitor.md)

## 需求分析相關

- [Requirements Analysis](./RequirementsAnalysis.md)

## 理性懷疑原則

- 模式是有用的指南, 但也是危險的工具
- 應該將它們用作一種 __思考問題的輔助手段__, 而不是解決問題的處方
- 使用模式時, 小心以下常見錯誤

| 錯誤     | 產生條件 |
| -------- | ------- |
| 浮於表面 | 僅對低層情況有了一些膚淺的理解, 就草草選擇一個模式 |
| 偏見 | 對模式過於偏信。 根據已經選定的模式/模型來解釋所有資料, 不願意對自己的偏見有任何質疑 | 
| 錯選 | 不理解模式適用的背景和條件(對各模式的分類關係理解不全), 選擇了錯誤的模式 | 
| 誤判 | 不熟悉各種模式, 因為無知而導致誤判 | 
| 削足適履 |  忽略了實際的, 具體實體行為中的例外情況, 因為它們似乎不符合模式中所表達的理論。<br/> 很可能會使所建模出來的物件過於僵硬, 不符合實際情況 | 

