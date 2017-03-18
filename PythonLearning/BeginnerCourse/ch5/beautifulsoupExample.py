# -*- coding: utf-8 -*-
"""
Created on Sat Mar 18 21:37:17 2017

@author: haochinnate
"""

import requests
from bs4 import BeautifulSoup


# use "requests" package to get the source code of webpage
url = "http://www.taiwanlottery.com.tw/"
html = requests.get(url)

# use html.parser to analyze source code
sp = BeautifulSoup(html.text, "html.parser")

# title (the title of webpage)

# text (get the webpage text content after remove all tag)

# find (return the first tag which match the condition)

# find_all (return all tags that match the condition)

# select (return the content of CSS selector)




