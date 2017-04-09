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
# make a database connection
conn = sqlite3.connect("PM25Database.sqlite")
cursor = conn.cursor()

# create a table
sqlstr = '''
CREATE TABLE IF NOT EXISTS Table25 (
    "no" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE , 
    "SiteName" TEXT NOT NULL,
    "County" TEXT NOT NULL,
    "Status" TEXT NOT NULL,
    "PSI" INTEGER NOT NULL,
    "PM10" INTEGER NOT NULL,
    "PM25" INTEGER NOT NULL,
    "PublishTime" TEXT NOT NULL)
'''
cursor.execute(sqlstr)

# read the web page content
url = "http://opendata.epa.gov.tw/ws/Data/REWXQA/?$orderby=SiteName&$skip=0&$top=1000&format=json"
html = requests.get(url).text.encode('utf-8-sig')

# create md5
md5Obj = hashlib.md5(html).hexdigest()
old_md5 = ""

# read old md5, and write new md5 into file
if os.path.exists("oldMD5.txt"):
    with open("oldMD5.txt", "r") as f:
        old_md5 = f.read()
        
with open("oldMD5.txt", "w") as f:
    f.write(md5Obj)
    

# compare old md5 and new md5 to determine the data is updated or not
if md5Obj != old_md5:
    print("the data had updated...")
    sp = BeautifulSoup(html, "html.parser")
    
    jsonData = ast.literal_eval(sp.text)
    
    conn.execute("delete from Table25")
    conn.commit()
    
    n = 1
    for site in jsonData:
        # the key in site[] have to be same as json data property
        tmpSiteName = site["SiteName"]
        tmpCounty = site["County"]
        tmpStatus = site["Status"]
        tmpPSI = 0 if site["PSI"] == "" else int(site["PSI"])
        tmpPM10 = 0 if site["PM10"] == "" else int(site["PM10"]) 
        tmpPM25 = 0 if site["PM2.5"] == "" else int(site["PM2.5"])
        tmpPublishTime = site["PublishTime"]
        print("SiteName: {}(in {}), Status = {}, PSI = {}, PM1.0 = {}, PM2.5 = {}, Time: {}".format(
                tmpSiteName, tmpCounty, tmpStatus, tmpPSI, tmpPM10, tmpPM25, tmpPublishTime))

        sqlStr = "insert into Table25 values({},'{}','{}','{}',{},{},{},'{}')".format(
                n, tmpSiteName, tmpCounty, tmpStatus, tmpPSI, tmpPM10, tmpPM25, tmpPublishTime)
    
        cursor.execute(sqlStr)
        n += 1
        conn.commit()
        
    
else:
    print("the data didnot update, read from the database...")
    cursor = conn.execute("select * from Table25")
    rows = cursor.fetchall()
    
    for row in rows: # row is tuple, cannot use string as index, use integers... not quiet good
        #print("SiteName: {}(in {}), Status = {}, PSI = {}, PM1.0 = {}, PM2.5 = {}, Time: {}".format(
        #        row["SiteName"], row["County"], row["Status"], row["PSI"], row["PM10"], row["PM25"], row["Publishtime"]))
        print("SiteName: {}(in {}), Status = {}, PSI = {}, PM1.0 = {}, PM2.5 = {}, Time: {}".format(
                row[1], row[2], row[3], row[4], row[5], row[6], row[7]))

conn.close()
