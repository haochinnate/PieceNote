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
print(mainContent)


# class: gap_b20

