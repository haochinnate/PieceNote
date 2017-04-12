# -*- coding: utf-8 -*-
"""
Created on Sun Apr  9 18:08:35 2017

@author: haochinnate
"""

from selenium import webdriver
from time import sleep

urlList = ['https://www.u-car.com.tw/', 
           'http://www.cpbl.com.tw/standing/year.html',
           'https://www.google.com.tw/'] # ,
           #'http://www.baseball-reference.com/']

# use selenium to control the browser
browser = webdriver.Chrome()

browser.maximize_window()

#link to specific website
for url in urlList:
    browser.get(url) 
    sleep(3)
    

browser.close()



