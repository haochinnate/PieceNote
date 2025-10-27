# Part 1 - Data PreProcessing

## Machine Learning Workflow

1. Data Pre-Processing
  - Import the data
  - Clean the data
  - Split into training and test sets
  - Feature Scaling
    
2. Modelling
  - Build the model
  - Train the model
  - Make predictions

3. Evaluation
  - Calculate performance metrics
  - Make a verdict

### Feature Scaling

- Always apply to columns (作用到每筆資料的某些屬性, 一次一個 column?)
  - neve apply across columns

1. Normalization 
  - X' = (X - Xmin) / (Xmax - Xmin)
  - 效果範圍: [ 0;1 ]

2. Standardization
  - X' = (X - u) / sigma
  - 效果範圍: [ -3; +3 ]

## Section 3: Data Preprocessing in python

- 從 data_preprocessing_tools.ipynb 開始

### Toolkits 

- Importing the libraries

```python

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# in exercise
from sklearn.model_selection import train_test_split
```

### Importing the dataset

```python

# create the data frame
dataset = pd.read_csv('Data.csv') 

# entities/features/independent variables 
# the matrix of features, [row indexes, column indexes]
# ':' is range
# ':-1' is all columns except the last one
X = dataset.iloc[:, :-1].values

# dependent variables (last columns, "Purchased" in example)
y = dataset.iloc[:, -1].values
```

### Taking care of missing data

```python

from sklearn.impute import SimpleImputer
# 用推算的方式補充 missing data (這邊用 mean) (missing value 也有可能是 0)

imputer = SimpleImputer(missing_values=np.nan, strategy='mean')
# all row : 
# columns: 1:3 (column 1 and 2, no column 0)
imputer.fit(X[:, 1:3]) 

# transform return the new updated version 
X[:, 1:3] = imputer.transform(X[:, 1:3])

print(X)
```



### Encoding the Independent Variable

- Handling Categorical Features
  - 範例中, 三個地名不是變成 0,1,2 
  - 而是 [1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]
  - 'Country' column 變為 3個 columns

```python

from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder

# [0] for 'Country' column
# remainder: reserve other columns
ct = ColumnTransformer(transformers=[('encoder'), OneHotEncoder(), [0]], remainder='passthrough')

X = np.array(ct.fit_transform(X))

print(X)
```


### Encoding the Dependent Variable

- LabelEncoder 

```python

from sklearn.preprocessing import LabelEncoder
le = LabelEncoder()
y = le.fit_transform(y)

```


### Splitting the dataset into the Training set and Test set

- "Feature Scaling" 應該要在 "splitting training/test set" 之後

- test set 不應該參與 training model, prevent information leakage
  - feature scaling 會計算 mean, sigma, Xmin, Xmax

```python
from sklearn.model_selection import train_test_split

# random_state, just for demo that will have same split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, random_state = 1)
```

### Feature Scaling

- to avoid dominated feature 
1. Standardisation
  - 適合大多數情況
2. Normalisation
  - 適合 feature 是常態分布

```python 

from sklearn.preprocessing import StandardScaler

sc. = StandardScaler()

# only apply feature scaling on numerical variables?
# don't apply on dummy variables (likes 'Country'?) 
# only 'Age' and 'Salary' column
X_train[:, 3:] = sc.fit_transform(X_train[:, 3:])

X_test[:, 3:] = sc.transform(X_test[:, 3:])

```
