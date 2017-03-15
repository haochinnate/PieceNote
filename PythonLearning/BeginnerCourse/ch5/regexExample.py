# -*- coding: utf-8 -*-
"""
Created on Wed Mar 15 22:23:49 2017

@author: haochinnate
"""

# use regular expression to extract page content
# re package

import re

# compile method, to create a object represent regular expression
pat = re.compile('[a-z]+')

# match() mehtod of regex object
matchObject = pat.match("qqtest123gggstring")
print(matchObject) # a _sre.SRE_Match object 
print(matchObject.group()) # group()  qqtest
print(matchObject.start()) # 0
print(matchObject.end()) # 6
print(matchObject.span()) # (0,6)

# match method, likes regexObject.match()
# matchObject = re.match(r'[a-z]+', "qqtest123gggstring")

# search() method of regex object, 
# match will start compare from first character
# search method will find in the whole string 
testStrStartWithNumber = "451gggtmp123testString"

noneMatchObject2 = pat.match(testStrStartWithNumber)
print(noneMatchObject2) # match() get None

matchObject2 = pat.search(testStrStartWithNumber)
print(matchObject2) # search() get gggtmp


