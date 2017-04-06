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
conn = sqlite3.connect("PM25Database.sqlite")
cursor = conn.cursor()

sqlstr = '''
CREATE TABLE IF NOT EXISTS Table25 (
    "no" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE , 
    "SiteName" TEXT NOT NULL,
    "County" TEXT NOT NULL,
    "Status" TEXT NOT NULL,
    "PSI" INTEGER
    "PM10" INTEGER
    "PM25" INTEGER)
'''

url = "http://opendata.epa.gov.tw/ws/Data/REWXQA/?$orderby=SiteName&$skip=0&$top=1000&format=json"
html = requests.get(url).text.encode('utf-8-sig')


