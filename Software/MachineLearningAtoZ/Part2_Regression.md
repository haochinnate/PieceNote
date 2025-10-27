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

### 

## Section 8: Polynomial Regression

## Section 9: Support Vector Regression (SVR)

## Section 10: Decision Tree Regression

## Section 11: Random Forest Regression

## Section 12: Evaluating Regression Models Performance

## Section 13: Regression Model Selection in Python