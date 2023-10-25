

# resources

- [How to Crack Any System Design Interview](https://www.youtube.com/watch?v=o-k7h2G3Gco)

## 準備 System Design 問題

1. 將 ambiguous problem statement 轉變為 concrete technical requirements
2. 建立一個 architecture and design 可以符合這些 requirements
3. articulate and defend your design decisions throughout the discussion


## Common Patterns

1. Layered Architecture
  - Presentation Layer
  - Business Layer
  - Persistance Layer
  - Database Layer
2. Event-Driven Architecture
  - Event Producer 
  - Message Broker
  - Event Consumer
  - eg: Command Query Responsibility Segregation (CQRS)
    - 分成 write operation(commands) 和 read operation(queries)
3. microkernel architecture
  - 有一個 core system, 然後將 functionality 切割成數個小的 micro kernel (plug-in component)
4. micro service architecture
  - 將 application 拆分為 small loosely coupled services, 會有自己的 data model, 然後利用 API 溝通
5. monolithic architecture
  - user interface + single instance + database, bundle together and run as a single unit





