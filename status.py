#!/usr/bin/python
import cgi
import cgitb
import sys
cgitb.enable()
print("Content-Type: text/html\n\n")
print("<html><body>")
form = cgi.FieldStorage()
cgi.print_form(form)
if "status" not in form:
	print("<h1>Error</h1>")
	print("<p>Please enter a status.</p></body></html>")
else:
	print(form['status'].value)
	status = form['status'].value
	f = open('status.txt', 'a')
	f.write(str(form['username'].value) + ' ' + status + '\n')
	f.close()

