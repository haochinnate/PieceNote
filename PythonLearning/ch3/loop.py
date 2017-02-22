# -*- coding: utf-8 -*-
"""
Created on Wed Feb 22 18:38:17 2017

@author: haochinnate
"""

# list 串列名稱 = [元素1, 元素2, ...]
list1 = [1, 2, 3, 4, 5]
list2 = ["香蕉", "芭樂", "蘋果"]
print(list1[0]) # 1
print(list2[1]) #芭樂

# -1 表示最後一個元素     
print(list2[-1]) # 蘋果

# 2維串列
list5 = [["joe", "1234"],
         ["judy", "abcd"],
         ["david", "5678"]]

# range function
# 串列變數 = range(整數值 n) (0 ~ n-1)
list6 = range(5) # 0~4
print(list6)

# 串列變數 = range(start, end) (start ~ end-1) 
list7 = range(3, 8)
tmp = list7[2] + list6[2]

# 串列變數 = range(start, end, interval) 
list8 = range(3, 8, 2)
print(list8)
list9 = range(8, 3, -2)
print(list9[2])


# for loop
# for 變數 in 串列 :
    # 程式區塊
for s in list2:
    print(s, end=",")
print()
    

# nest loop
for i in range(1, 10):
    for j in range(1,10):
        product = i * j
        print("%d * %d = %-2d  " % (i, j, product), end="")
    print()


# for else loop
# for 變數 in 串列:
#    區塊1
#    if(條件式):
#       區塊2
#       break
# else:
#    區塊3
   
n = int(input("請輸入一個大於1的整數: "))
if (n==2):
    print("2是質數!")
else:
    for i in range(2,n):
        if (n % i == 0):
            print("%d 不是質數!" % n)
            break
    else:
         print("%d 是質數!" % n)

# while loop
# while (條件式):
#   程式區塊

total = person = score = 0
while (score != -1):
    total += score
    person += 1;
    score = int(input("請輸入第 %d 位學生的成績: " % person))
    if score == -1:
        person -= 1
        
average = total/person
print("Total: %d, Average: %5.2f" %(total, average))

