#!/usr/bin/python

import cgi
import cgitb
import sys

cgitb.enable()

print "Content-Type:text/html\n\n"

inpt = sys.stdin.readline()
inputlist = inpt.split("&")

intlist = []
for string in inputlist:
	string = string.replace("+", "")
	intlist.append(string.split("="))

friendslist = []
for arg in intlist:
	if arg[1] == "on":
		friendslist.append(arg[0])
	elif arg[0] == "currentuser":
		user = arg[1]

if not friendslist:
	failed = open("nofriends.html", "r")
	x = 0
	while True:
		line3 = failed.readline()
		if x == 32:
			print "Return to Dashboard?"
			print "<form name=\"return\" action=\"http://cs.mcgill.ca/~jmerri8/dashboard.py\" method=\"post\">"
			print "<input type=\"hidden\" name=\"currentuser\" value=\"", user, "\">"
			print "<input type=\"submit\" name=\"submit\" value=\"dashboard\">"
			print "</form>"
			x = x+1
		elif not line3:
			break
		else:
			print line3
			x = x+1
else:
	tmpfile =open("tmp.txt", "w+")
	friend = open("friends.txt", "r+")

	while True:
		line = friend.readline()
		if not line:
			print "Internal error, unable to locate your friends list"
			break
		tmplist = line.split()
		if tmplist[0] == user:
			break
		else:
			tmpfile.write(line)
	line = line.replace("\n", " ")
	for friends in friendslist:
		line=line+friends+" "
	line = line + "\n"

	tmpfile.write(line)
	while True:
		line = friend.readline()
		if not line:
			break
		else:
			tmpfile.write(line)

	friend.seek(0)
	friend.truncate()
	tmpfile.seek(0)

	while True:
		line2 = tmpfile.readline()
		if not line2:
			break
		else:
			friend.write(line2)

	tmpfile.close()
	friend.close()
	
	success = open("addfriend.html", "r")
	z = 0
	while True:
		line5 = success.readline()
		if z == 32:
			for friends in friendslist:
				print friends, "<br>"
			
			print "<br>","Return to Dashboard?"
			print "<form name=\"return\" action=\"http://cs.mcgill.ca/~jmerri8/dashboard.py\" method=\"post\">"
			print "<input type=\"hidden\" name=\"currentuser\" value=\"", user, "\">"
			print "<input type=\"submit\" name=\"submit\" value=\"dashboard\">"
			print "</form>"
			z = z+1
		elif not line5:
			break
		else:
			print line5
			z = z+1
	success.close()

