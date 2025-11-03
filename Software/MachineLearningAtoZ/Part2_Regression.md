# Part 2 - Regression

## Section 6: Simple Linear Regression

### Equation

- y^ = b0 + b1*X1
  - y^: dependent variable
  - X1: independent variable
  - b0: y-intercept (constant)
  - b1: slope coefficient

### Ordinary Least Squares Regression

- 評量哪個 regression line 是最好的
- project on line
- residual: episolon_i = y_i - y^_i
  - 實際點的 y 座標 減去 映射在回歸線上的 y 座標
- 最好的線: SUM(y_i - y^_i)^2 是最小的


### LinearRegression class 

- 程式 simple_linear_regression.ipynb

- Training the Simple Linear Regression model on the Training set

```python

from sklearn.linear_model import LinearRegression
regressor = LinearRegression()
# features(independent variables) and dependent variable
regressor.fit(X_train, y_train)

```

- Predicting the Test set results

```python

y_pred = regressor.predict(X_test)

```

### Visualization

```python
from matplotlib.pyplot as plt

plt.scatter(X_train, y_train, color = 'red')
# plot regression line (use X_train)
plt.plot(X_train, regressor.predict(X_train), color = 'blue') 
plt.title('Salary vs Experience (Training set)')
plt.xlabel('Years of Experience')
plt.ylabel('Salary')
plt.show()
```

## Section 7: Multiple Linear Regression

### Equation

- y^ = b0 + b1*X1 + b2X2 + ... + bnXn
  - y^: dependent variable
  - Xi: independent variable
  - b0: y-intercept (constant)
  - bi: slope coefficient

### Assumptions of Linear Regression

- 另外有 pdf 在 google drive: Appendix1_Assumptions-of-Linear-Regression.pdf

1. Linearity
  - Linear relationship between Y and each X
2. Homoscedasticity(同質變異數)
  - equal variance
3. Multivariate Normality
  - Normality of error distribution 
4. Independence 
  - of observations. Includes "no autocorrelation"
5. Lack of Multicolinearity
  - 多重共線性（Multicollinearity）是指在多元線性回歸模型中，兩個或多個自變數之間存在高度相關性，這會導致模型估計不準確、係數變動劇烈，並使單一預測值的影響難以判斷。
  - Predictors are not correlated with each other
6. The Outlier Check
  - 這項不算 assumption, but an "extra"

### Dummy Variables(Handle Categorical Variables)

- 範例中的 column: Profit, R&D Spend, Admin, Marketing, State
  - Profix 是 indepenent variable
  - State 是 Categorical Variables

- 把 State 轉成 Dummy variables

### Dummy Variable Trap

- D2 = 1 - D1
- y = ... + b4D1 + b5*D2 不可以同時把全部 dummy variables 都加入
  - 有三個的話, 只加兩個
  - __Always omit one dummy variable__

### P-value and Hypothesis Testing(假說檢定)

- statistical significance 顯著性差異

### Backward Elimination

#### 建立 models 的五種方法

1. All-in (all variables)
  - prior knowledge
  - You have to  
  - Preparing for backward elimination
2. Backward Elimination
  - 決定一個 significance level (e.g.: SL = 0.05)
  - fit the full model with all possible predictors
  - 找出 P-value 最大的 predictor (P > SL, 則下一步; P <= SL, 表示找到)
  - 移除該 predictor
  - Fit model without this variable*
3. Forward Selection
  - 決定一個 significance level to enter the model
  - fit all simple regression models, 選擇最低的 P-value 
  - Keep this variable and fit all possible models with one extra predictor add to the one(s) you already have
  - 找出最低 P-value 的 predictor, 如果 Ｐ < SL, 則回上一步; P > SL, 則previous model就是最佳解
4. Bidirectional Elimination
  - significance level: SL_ENTER, SL_STAY
5. Score Comparison
  - N variables -> 2^N - 1 個組合 possible regression models

- 3,4,5 又叫 Stepwise Regression

### code

#### encoding categorical data (OneHotEncoder)

```python
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder
# [3] is "State" column
ct = ColumnTransformer(transformers=[('encoder', OneHotEncoder(), [3])], remainder='passthrough')
X = np.array(ct.fit_transform(X))
```

#### Training the Multiple Linear Regression model

```python

# 會幫忙處裡 Dummy Variable Trap, 所以不用移除 column
from sklearn.linear_model import LinearRegression
regressor = LinearRegression()
regressor.fit(X_train, y_train)

```

#### Predicting the Test set results

```python
y_pred = regressor.predict(X_test)
np.set_printoptions(precision=2)
print(np.concatenate((y_pred.reshape(len(y_pred),1), y_test.reshape(len(y_test),1)),1))

```

## Section 8: Polynomial Regression

## Section 9: Support Vector Regression (SVR)

## Section 10: Decision Tree Regression

## Section 11: Random Forest Regression

## Section 12: Evaluating Regression Models Performance

## Section 13: Regression Model Selection in Python