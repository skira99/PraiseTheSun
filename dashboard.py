#!/usr/bin/python

import cgi
import cgitb

cgitb.enable() 

print("Content-Type: text/html\n\n")
f = open('dashboard.html', 'r')
print(f.read())
f.close()
newsfeed = open('status.txt', 'r')

strings = list(newsfeed)
strings.reverse()
strings = strings[0:20]
for string in strings:
	print(string)
newsfeed.close()
print("</body></html>")

