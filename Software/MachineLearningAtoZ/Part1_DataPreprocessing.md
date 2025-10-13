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
# 用推算的方式補充 missing data (這邊用 mean)

imputer = SimpleImputer(missing_values=np.nan, strategy='mean')
imputer.fit(X[:, 1:3])
X[:, 1:3] = imputer.transform(X[:, 1:3])


```

### Encoding the Independent Variable

```python

from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder

ct = ColumnTransformer(transformers=[('encoder'), OneHotEncoder(), [0]], remainder='passthrough')

X = np.array(ct.fit_transform(X))

print(X)
```


### Encoding the Dependent Variable

```python



```
