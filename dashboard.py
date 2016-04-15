#!/usr/bin/python

import cgi
import cgitb
import sys

def getusername():
	infostring = sys.stdin.readline()
	infolist = infostring.split('&')
	for i in range(len(infolist)):
		if infolist[i].startswith("currentuser"):
			infostring = infolist[i]
			infolist = infostring.split('=')
			break
		else:
			continue
	return str(infolist[1])

def getfriends(user):
	with open('friends.txt') as fp:
    		for line in fp:
        		if line.startswith(user):
				return line.split(' ')
	return


def printnewsfeed(user):
	newsfeed = open('status.txt', 'r')
	strings = list(newsfeed)
	strings.reverse()
	friends = getfriends(user)
	i = 0
	for string in strings:
		if i < 20:
			for friend in friends:
				if string.startswith(str(friend)):
					print(string + '</br>')
					i += 1
					break
		else:
			break
	newsfeed.close()

def printhtml(usr):
	print('<html><head><title>dashboard</title></head><body><h1> Dashboard </h1>')
	print('<ul><li><a href="http://cs.mcgill.ca/~sthibo6/welcome.html">logout</a></li></ul></br>')
	print('<form name="makefriend" action="http://cs.mcgill.ca/~sthibo6/makeafriend.py" method="post">')
	print('<input type="hidden" name ="currentuser"  value="%s">' % (user))
	print('<input type="submit" name ="makeafriend" value="Make a Friend"></form>')
	print('<form name="seefriend" action="http://cs.mcgill.ca/~jmerri8/seefriends.cgi" method="post">')
	print('<input type="hidden" name ="currentuser"  value="%s">' % (user))
	print('<input type="submit" name ="seeafriend" value="See a friend"></form>')
	print('<form name="status" action="http://cs.mcgill.ca/~jmerri8/status.py" method="post"><b>Enter a Status Update:</b></br>')
	print('<input type="hidden" name="currentuser" value ="%s">' % (user))
	print('<input type="text" name="status"></br>')
	print('<input type="submit" name="submit" value = "Update Status"></form>')
print("Content-Type: text/html\n\n")
user = getusername()
printhtml(user)
printnewsfeed(user)
print("</body></html>")

