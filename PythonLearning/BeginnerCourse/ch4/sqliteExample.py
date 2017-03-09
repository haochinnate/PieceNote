# -*- coding: utf-8 -*-
"""
Created on Thu Mar  9 22:38:07 2017

@author: haochinnate
"""

import sqlite3

# create connection
sqlConnection = sqlite3.connect("sampleSQLite.sqlite")

# create cursor object
cursor - sqlConnection.cursor()

