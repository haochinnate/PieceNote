# -*- coding: utf-8 -*-
"""
Created on Tue Feb 21 20:23:42 2017

@author: haochinnate
"""

# 變數 = input([提示字串])
score = input("please input the score: ")
print(score)

# // : 取得整除的商數
print(32//5)

# ** 次方
print(10**3)

# if statement: if(條件式):
if (int(score) >= 60):
    print("pass")

pw = input("please input password: ")
if (pw=="1234"):
    print("correct password")
 
# if...elif...else
if (int(score) >= 90):
    print("優等")
elif (int(score) >= 80):
    print("甲等")
elif (int(score) >= 70):
    print("乙等")
elif (int(score) >= 60):
    print("丙等")
else:
    print("丁等")
    print("so bad...")

    
  