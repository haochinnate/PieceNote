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

# tuple, tuple裡ˇ的元素個數和內容都不能改
# 元素名稱 = (元素1, 元素2, ...)
tuple1 = ( 1, "test", 2)
n = len(tuple1)
# tuple 比list 優點: 執行速度快, 資料較安全

# tuple to list
list2 = list(tuple1)
list2.append("test2")

# list to tuple
tuple2 = tuple(list2)

# dictionary
# 字典名稱 = { key1: value1, key2:value2, ... }
dict1 = { "Kershaw": 20, "Trout": 30, "Archer":15}
dict2 = { 20:"Kershaw", 30:"Trout", 15:"Archer"}
dict3 = { "Kershaw": 20, 30:"Trout", True:15}

print(dict1["Kershaw"])
# print(dict2["Kershaw"]) # fail, error
print(dict2[30])
print(dict3[30])
print(dict3["Kershaw"])
print(dict3[True])
# print(dict3[15]) # fail, error

# delete specific item in dictionary > del dict[key] 
del dict1["Archer"]

# delete all items in dictionary > dict.clear()
dict2.clear()

# delete whole dictionary
dict4 = dict3.copy()
del dict3

# dict.keys(), dict.values(), dict.items()
keyOfDict1 = list(dict1.keys())
valuesOfDict1 = list(dict1.values())
itemsOfDict3 = list(dict4.items())
for i in range(len(keyOfDict1)):
    print("Player: %s, number: %d." % (keyOfDict1[i], valuesOfDict1[i]))
print()

for key, value in itemsOfDict3:
    print("Key is %s, Value is %s" % (str(key), str(value)))
print()    

    
# dict.get() and dict.setdedault()
# dict.get(key [, default value])
testdict = { "Kershaw": 20, "Trout": 30, "Archer":15} 
n1 = testdict.get("Kershaw") # n = 20
n2 = testdict.get("Trout", 50) # n = 30
n3 = testdict.get("Tanaka") # n = None (NoneType)
n4 = testdict.get("Tanaka", 99) # n = 99
print("n1: %d, n2: %d, n3: %s, n4: %d" % (int(n1), int(n2), str(n3), int(n4)))

# dict.setdefault(key [, default value])
# if key exist, value in dictionary will not change
# if key doesn't exist, 
#       then add key:None to dictionary
# if key doesn't exist and has default value, 
#       then add key:defaultValue to dictionary
testdict2 = { "Kershaw": 20, "Trout": 30, "Archer":15} 
n5 = testdict2.setdefault("Kershaw") # n = 20
n6 = testdict2.setdefault("Trout", 50) # n = 30
n7 = testdict2.setdefault("Tanaka") # n = None (NoneType)
n8 = testdict2.setdefault("Rodriguez", 87) # n = 99
print("n5: %d, n6: %d, n7: %s, n8: %d" % (int(n5), int(n6), str(n7), int(n8)))


