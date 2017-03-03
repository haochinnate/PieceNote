# -*- coding: utf-8 -*-
"""
Created on Fri Mar  3 18:59:50 2017

@author: haochinnate
"""

# os package
import os

# os.remove("file.txt")
# os.mkdir("testFolder")
# os.rmdir("testFolder")

# os.system(command) execute os command

# os.path
currentPath = os.path.dirname(__file__)
print("current path: " + currentPath)

fileFullPath = os.path.abspath(__file__)
print("file full path: " + fileFullPath)

fileName = os.path.basename(__file__)
print("file name: " + fileName)


# os.walk, walk through all directory and file in specific path
driveC = os.path.dirname("..\\..\\")
treeStructure = os.walk(driveC)

for dirname, subdirs, files in treeStructure:
    print("directory: ", dirname)
    print("all dir: ", subdirs)
    print("all files", files)
    print()

# shutil package, to process file cross platform
# import shutil

# glob package, get the files that match the condition
import glob
#files = glob.glob("..\\..\\") + glob.glob("loop*.py") 
files = glob.glob("*.py") 
for file in files:
    print(file)



