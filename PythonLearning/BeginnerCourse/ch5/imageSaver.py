# -*- coding: utf-8 -*-
"""
Created on Wed Mar 29 22:24:16 2017

@author: haochinnate
"""
import requests, os
from bs4 import BeautifulSoup
from urllib.request import urlopen

# use "requests" package to get the source code of webpage
url = "http://www.cpbl.com.tw/cpbl.html"
html = requests.get(url)
html.encoding = "utf-8"

# use html.parser to analyze source code
sp = BeautifulSoup(html.text, "html.parser")

# save the image in this folder
imageFolder = r"D:\CodingWorkspace\images"

if not os.path.exists(imageFolder):
  os.mkdir(imageFolder)

# get all tag with <a> and <img>
allLinks = sp.find_all(['a', 'img'])


for link in allLinks:
    src = link.get('src')
    href = link.get('href')
    attrs = [src, href]
    
    for attr in attrs:
        if (attr!=None) and (".jpg" in attr or ".png" in attr):
            
            # analyze and concatenate the file name
            fullPath = attr
            fileName = fullPath.split('/')[-1] # the last one is file name
            extension = fileName.split('.')[-1] 
            fileName = fileName.split('.')[-2]
            
            if "jpg" in extension:
                fileName = fileName + ".jpg"
            else:
                fileName = fileName + ".png"
               
            # 
            try:
                #image = urlopen(fullPath)
                #f = open(os.path.join(imageFolder, fileName), "wb")
                #f.write(image.read())
                #f.close()
                print(fullPath)
            except:
                print("Cannot save {}".format(fileName))
            
            
        
        