# -*- coding: utf-8 -*-
"""
Created on Thu Mar  2 22:16:51 2017

@author: haochinnate
"""

# function 宣告方式
# def functionName([arg1, arg2, ...]):
#     function statement
#     [return val1, val2, ...]
def PrintHelloWorld():
    print("hello world")
    
def CalculateArea(width, height):
    area = width * height
    return area

PrintHelloWorld()
area1 = CalculateArea(3, 4.2)
print(area1)

# 參數順序改變
area2 = CalculateArea(height=2, width=3.5)

# default value of argument
# the argument with default value have to put at the end of arguments
def CalculateArea(width, height = 4):
    area = width * height
    return area

area3 = CalculateArea(5.2)

# flexible number of arguments, the args will save as tuple
# def functionName(* args):
def FlexibleArgsFunctioin(*args, base):
    total = 0
    for arg in args:
        total += arg
    
    baseSquare = base*base
    return baseSquare, total

getReturnValue = FlexibleArgsFunctioin(3, 4, 5, base = 10)
    
# if you want to use global variable in method 
# then declare with "global" keyword

# import packageName
import random
random.seed()

# from packageName import *
# (import all method in package, and use method don't have to package name)

# from packageName import method1, method2, ...
# (onlt import some method in package)

# import packageName as alias
# (use alias to call package method)
 
