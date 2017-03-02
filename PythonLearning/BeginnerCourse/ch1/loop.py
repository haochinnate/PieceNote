# -*- coding: utf-8 -*-
"""
Created on Sat Feb 18 18:24:26 2017

@author: qiner
"""

sum = 0
def show(n):
    print("第 " + str(n) + " 次執行迴圈")

for i in range(1,11):
    show(i)
    sum += i
    
print("sum = " + str(sum))

