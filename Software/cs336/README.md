# CS336 Language Modeling From Scratch

## 1. Overview and Tokenization

- GPT4 有 1.8T 個參數, 花了 $100M 美元訓練
- 建立 small language models (<1B 的參數)
- 三種知識
  - Mechanics(事務運作的機制): how things work
  - Mindset(思維方式): squeezing the most of the hardware (scale)
  - Intuitions(直覺): which data and modeling decision

- accuracy = efficiency x resources
- Maximize Efficiency!

### Levels of openness

- Closed models (e.g., GPT-4o): API access only
    
- Open-weight models (e.g., DeepSeek): weights available, paper with architecture details, some training details, no data details
 
- Open-source models (e.g., OLMo): weights and data available, paper with most details (但未必包含設計理念或失敗的實驗)。

### Design decisions

#### Basics（基礎）

- Tokenization: 分詞 / 標記化
  - Byte-Pair Encoding (BPE) tokenizer  [Sennrich+ 2015]
- Architecture: 架構
  - Attension is all you need [Vaswani+ 2017]
  - MLP: dense, mixture of experts [Shazeer+ 2017]
    - Outrageously Large Neural Networks: The Sparsely-Gated Mixture-of-Experts Layer
- Loss function: 損失函數
- Optimizer: 優化器
  - AdamW, Muon, SOAP
- Learning rate: 學習率

#### Systems（系統）

- Kernels: 核心 / 核函數(通常指 GPU 計算核心)
- Parallelism: 並行計算 / 平行處理
- Quantization: 量化
- Activation checkpointing: 激活檢查點（一種節省顯存的技術）
- CPU offloading: CPU 卸載（將運算或數據轉移至 CPU 處理）
- Inference: 推論
  - Two phases: prefill and decode 

#### Scaling laws（擴展定律 / 縮放定律）

- Scaling sequence: 序列擴展
- Model complexity: 模型複雜度
- Loss metric: 損失指標
- Parametric form: 參數形式
- Compute-optimal scaling laws: [Kaplan+ 2020][Hoffmann+ 2022]

#### Data（數據 / 資料）

- Evaluation: 評估
- Curation: 數據精選 / 策展（指資料的篩選與整理）
- Transformation: 轉換
- Filtering: 過濾
- Deduplication: 去重 / 刪除重複
- Mixing: 混合 / 配比（指不同數據源的比例）

#### Alignment（對齊）

- Supervised fine-tuning: 監督式微調 (SFT)
- Reinforcement learning: 強化學習 (RL)
- Preference data: 偏好數據
- Synthetic data: 合成數據
- Verifiers: 驗證器


### Tokenization 

- [Tokenization](./Tokenization.md)


## 2. Pytorch, Resource Accounting 

- [Lecture2](./Lecture2.md)



## 3. 