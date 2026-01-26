# Tokenization 

- So we need a procedure that encodes strings into tokens.
- We also need a procedure that decodes tokens back into strings.
- A  __Tokenizer__ is a class that implements the encode and decode methods.
- The **vocabulary size** is number of possible tokens (integers).

- 種類
  - Character-based tokenization
    - vocabulary size 會很大, 每個 character 的出現頻率不一樣
  - Byte-based tokenization
    - 壓縮率 1 byte per token, 太差了
  - Word-based tokenization
    - 無法知道 vocabulary size 

## Byte Pair Encoding (BPE)

- 基本概念： 利用原始文本來訓練分詞器（Tokenizer），藉此自動決定詞彙表（Vocabulary）。

- 直觀理解（Intuition）： 常見的字符序列由單一 Token（詞元）表示，而罕見的序列則由多個 Token 組合表示。

- GPT-2 的應用： GPT-2 論文使用了基於單詞的分詞方式（word-based tokenization），先將文本拆分為初始片段，然後在每個片段上執行原始的 BPE 演算法。

- 流程概要（Sketch）： 一開始將每個位元組（byte）視為一個 Token，接著逐步合併（merge）出現頻率最高的相鄰 Token 對。
- 

## Summary

- 分詞器 (Tokenizer)： 負責執行「字串」與「Token（索引）」之間的雙向轉換。

- 傳統方法的侷限： 基於字符 (Character-based)、位元組 (Byte-based) 或單詞 (Word-based) 的分詞方式，通常遠非最佳解 (highly suboptimal)。

- BPE 的優勢： BPE 是一種有效的啟發式方法 (heuristic)，它依賴語料庫的統計數據來進行分詞。

- 未來展望： 分詞目前是個「必要之惡」，或許未來有一天，我們能跳過這一步，直接從位元組 (bytes) 層面進行處理……

