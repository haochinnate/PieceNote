# -*- coding: utf-8 -*-
"""
Created on Mon Feb 20 21:47:47 2017

@author: haochinnate
"""

# 註解
# del 變數名稱

# variable
a = 20
del a
flag = True
flag2 = False

# string
str1 = "this is a string"
str2 = '"hello"'
str3 = "'hello2'"
str4 = "hello \n next line"

# print function
# print(項目1 [, 項目2, sep=分隔字元, end=結束字元])
print(str1, str2, str3)

print(str2, str3, str4, sep="&")

print(str2, str3, sep="&", end="")

name = "Felix"
score = 80 
# print(項目 % 參數列)
print("score of %s is %d" %(name, score))

# format 全部8, 小數點2
price = 23.8
price2 = 314.89
print("price is %8.2f" % price)
print("price is %8.2f" % price2)

# print(字串.format(參數列))
print("score of {} is {}".format(name, score))


# type(項目)
print(type(flag))
print(type(str4))
print(type(score))

# type convert
# int(), float(), str()
num3 = 23 + int("67")
print("score is " + str(score))


