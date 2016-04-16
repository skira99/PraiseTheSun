#!/usr/bin/python

import cgi
import cgitb
import fileinput
import sys

cgitb.enable()

print "Content-Type:text/html\n\n"

f = open("mkfriends.html", "r")

i = 0
while True:
	line = f.readline()
	if i == 32:
		break
	elif not line:
		break
	else:
		print line
		i = i+1
	

print "\t\t\t <form name=\"makefriends\" action=\"newfriends.py\" method=\"post\">"

hiddenuser = sys.stdin.readline()
hiddenlist = hiddenuser.split("&")
userlist = hiddenlist[0].split("=")
if userlist[0] == "currentuser":
	user = userlist[1]
else:
	print"\t\t\t\t Internal error, failed to retrieve current user"

friends = open("friends.txt", "r")
allusers = open("users.txt", "r")

while True:
	line2 = friends.readline()
	if not line2:
		print "\t\t\t\t Internal error, failed to retrieve friends list"
		break
	listfriend = line2.split()
	if (listfriend[0] == user):
		break

alluserslist = []

while True:
	line3 = allusers.readline()
	if not line3:
		break
	else:
		line3 = line3.replace("\n","")
		alluserslist.append(line3)

y=0
for elements in alluserslist:
	if y == len(alluserslist):
		break
	elif alluserslist[y] in listfriend:
		y = y+4
	else:
		print "\t\t\t\t",alluserslist[y], alluserslist[y+2],"<input type=\"checkbox\" name=\"",alluserslist[y],"\">" "<br><br>"
		y = y+4

print listfriend
print user

print "\t\t\t\t <input type=\"hidden\" name=\"currentuser\" value=\"", user, "\">"
print "\t\t\t\t<center> <input type=\"submit\" name=\"Submit\" value=\"Make Friends!\"></center>"
print "\t\t\t </form>"

while True:
	line = f.readline()
	if i ==35:
		print "<input type=\"hidden\" name=\"currentuser\" value=\"",user,"\">"
	if not line:
		break
	else:
		print line
		i = i+1
f.close()
