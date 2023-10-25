# Algorithms

- [Algorithms You Should Know Before System Design Interviews](https://www.youtube.com/watch?v=xbgzl2maQUU)

## Consistent Hashing 

- key hash 成 圓圈上的 point 
- 有增加/減少 server 時, 只要更動有關聯的 key 就好了
- balance the load within a cluster of services

## Quadtrees, Geohash

- 2D spatial indexing
- 其他: R-trees, KD Tree
- location based service

## Leaky Bucket

- rate limiting algorithm
- 其他: Token bucket algorithm, Sliding window counter algorithm

## Tries

- tree structure optimized for storing strings and prefixes
- fast lookup speed 
- search autocomplete

## One catch

- radix trie

## Bloom filter

- 對 item 做 hash, 然後某個 bit 設成1, 用來確認一個 item 有沒有存在於一個 set 中
- 不一定準...自己 trade off: less memory or less accurate

## Consensus algorithms (共識機制)

- Paxos and Raft
- ex: kafka, etcd
- consensus != consistency
- [一致性問題與共識演算法](https://rickhw.github.io/2018/08/11/DistributedSystems/Distributed-Consistency-and-Consensus-Algorithm/)


