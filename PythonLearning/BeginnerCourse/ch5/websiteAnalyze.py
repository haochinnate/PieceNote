# -*- coding: utf-8 -*-
"""
Created on Mon Mar 13 22:52:51 2017

@author: haochinnate
"""

# urllib package, urlparse method will return a tuple ParseResult object
from urllib.parse import urlparse

url = 'http://taqm.epa.gov.tw:80/pm25/tw/PM25A.aspx?area=1'
o = urlparse(url)

print(o)
print("sheme={}-{}".format(o.scheme, o[0]))
print("netloc={}-{}".format(o.netloc, o[1]))
print("path={}-{}".format(o.path, o[2]))
print("params={}-{}".format(o.params,o[3]))
print("query={}-{}".format(o.query, o[4]))
print("fragment={}-{}".format(o.fragment, o[5]))
print("port={}".format(o.port))


# requests package, get method
import requests

url2 = 'http://www.e-happy.com.tw'
html = requests.get(url2)
html.encoding = "UTF8"
print(html.text)  


# Beautifulsoup package?
