# -*- coding: utf-8 -*-
"""
Created on Thu Mar 30 23:02:28 2017

@author: haochinnate
"""

# use hashlib package to judge the document is updated  or not
import sqlite3, ast, hashlib, os, requests
from bs4 import BeautifulSoup

# create a md5 object
md5 = hashlib.md5()

# encrypt the string (b for binary?)
md5.update(b'Test String')

# 16bits encrypt result 
print(md5.hexdigest()) 


#---------------------------------
#conn = sqlite3.connect()
