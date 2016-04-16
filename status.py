#!/usr/bin/python
import cgi
import cgitb
import sys 

cgitb.enable()
print("Content-Type: text/html\n\n")
print("<html><body>")
form = cgi.FieldStorage()
user = str(form.getvalue('currentuser'))

if "status" not in form:
	print("<h1>Error</h1>")
	print("<p>Please enter a status.</p>")
	print('<form name="input" action="dashboard.py" method="post">')
	print('<input type="hidden" name="currentuser"  value="%s">' % (user))
	print('<input type="submit" name="submit" value="Return to Dashboard">')
	print('</form></body></html>')
else:
        status = form['status'].value
        f = open('status.txt', 'a')
        f.write(user + ' ' + status + '\n')
        f.close()
	print('<h3> Status Updated! </h3>')
        print('<form name="input" action="dashboard.py" method="post">')
	print('<input type="hidden" name="currentuser"  value="%s">' % (user))
	print('<input type="submit" name="submit" value="Return to Dashboard">')
	print('</form></body></html>')

