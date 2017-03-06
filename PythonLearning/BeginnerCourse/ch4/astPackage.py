# -*- coding: utf-8 -*-
"""
Created on Mon Mar  6 22:43:40 2017

@author: haochinnate
"""

import ast


    
def displayAccountsInfo():
    for account in accountData:
        print("{}-{}".format(account, accountData[account]))
    print()
        

def readAccountsInfo():
    with open("account.txt", "r", encoding="UTF-8-sig") as f:
        accountsString = f.read()
        # string to dictionary  
        accountData = ast.literal_eval(accountsString) 
        return accountData
    
        
accountData = dict()
accountData = readAccountsInfo()
displayAccountsInfo()

# add new data
accountData["testAccount"] = "passwordForTest"
displayAccountsInfo()
           
# save back to file
with open("account.txt", "w", encoding="UTF-8-sig") as f:
    f.write(str(accountData))

# read again to check is save access
accountData = readAccountsInfo()
displayAccountsInfo()

         