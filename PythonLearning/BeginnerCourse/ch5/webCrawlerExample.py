# -*- coding: utf-8 -*-
"""
Created on Wed Mar 22 22:33:07 2017

@author: haochinnate
"""

import requests
from bs4 import BeautifulSoup

url = "http://www.cpbl.com.tw/standing/year.html"
html = requests.get(url)
sp = BeautifulSoup(html.text, "html.parser")

# class: cont_single
mainContent = sp.find("div", {"class":"cont_single"})
#print(mainContent)


# class: gap_b20
allTableTitles = mainContent.find_all("h3", {"class":"gap_t20"})
#print(allTableTitles)

allTableContents =  mainContent.find_all("table", {"class":"std_tb mix_x"})
#print(allTableContents)

for tableContent in allTableContents:
    rows = tableContent.find_all("tr")
    
    # grid header
    for col in rows[0].find_all("th"):
        print(col.text, end='           ')
    print()
    
    # grid content
    for i in range(1, len(rows)):
        for col in rows[i].find_all("td"):
            print(col.text, end='   ')
        print()
         
