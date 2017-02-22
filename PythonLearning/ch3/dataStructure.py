# -*- coding: utf-8 -*-
"""
Created on Wed Feb 22 21:06:35 2017

@author: haochinnate
"""

list1 = [1, 2, 3, 4, 5, 6]
x = [8, 9]

# append 
list1.append(8)
for i in list1:
    print("%d, " % i, end = "")
print() 
    
list1.append(x) # array will add to list as one single element
for i in list1:
    print(i, end = " ")
print()
    
# extend
list1.extend(x)
for i in list1:
    print(i, end = " ")
print()

# tuple
