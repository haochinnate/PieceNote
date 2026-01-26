# Part 3 - Classification

- identify the **category** of new observations based on training data

## Section 16: Logistic Regression

- predict a categorical dependent variable from a number of independent variables

- ln(p/(1-p)) = b0 + b1X1

### Maximum Likelihood

- Likelihood, 所資料點屬於哪一類的機率相乘, 每一類都要
  - n 點
  - Y 類
  - n * Y 個機率值 全部相乘

```python

# splitting the dataset 
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.25, random_state = 0)

# feature scaling 
from sklearn.preprocessing import StandardScaler
sc = StandardScaler()
X_train = sc.fit_transform(X_train)
X_test = sc.transform(X_test)



```


## Section 17: K-Nearest Neighbors (K-NN)

## Section 18: Support Verctor Machine (SVM)

## Section 19: Kernel SVM

## Section 20: Naive Bayes

## Section 21: Decision Tree Classification

## Section 22: Random Forest Classification

## Section 23: Classification Model Selection in Python
