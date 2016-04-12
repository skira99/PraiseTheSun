import cgi
import sys
form = cgi.FieldStorage()
if form.has_key("status")
	status = form['status']
	target = open(status.txt, 'w')
	target.write(username, status, "\n")
	target.close()
else
	print("Content-Type: text/html")
	print("No status entered!")
	return
