# -*- coding: utf-8 -*-
"""
Created on Thu Mar  9 22:38:07 2017

@author: haochinnate
"""

import sqlite3

# create connection
sqlConnection = sqlite3.connect("sampleSQLite.sqlite")

# create cursor object
cursor = sqlConnection.cursor()

# delete the whole table
sqlstr = "DROP TABLE table01" 
cursor.execute(sqlstr)

# create a table 
sqlstr = 'CREATE TABLE IF NOT EXISTS table01 \
    ("num" INTEGER PRIMARY KEY NOT NULL , "tel" TEXT)'
# execute a sql command
cursor.execute(sqlstr)

# add a new record 
num0 = 2
tel0 = "02-123456780"
num1 = 3
tel1 = "02-781829231"
sqlstr = "insert into table01 values({}, '{}')".format(num0, tel0)
cursor.execute(sqlstr)
sqlstr = "insert into table01 values({}, '{}')".format(num1, tel1)
cursor.execute(sqlstr)

# update the database
sqlConnection.commit()

# clode the connection
sqlConnection.close()

# connection object also can execute SQL command

# delete the data which num is 1
# sqlstr = "delete from table01 where num=1"


# cursor() and execute() will both return a cursor object
# fetchall() function and fetchone() function
sqlConnection = sqlite3.connect("sampleSQLite.sqlite")
cursor = sqlConnection.execute("select * from table01")

rows = cursor.fetchall()
print(rows)
for row in rows:
    print("{}\t{}".format(row[0], row[1]))


sqlConnection.commit()
sqlConnection.close()