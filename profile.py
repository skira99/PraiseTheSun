#!/usr/bin/python

import cgi
import sys
import cgitb
def getprofile(name):
	userlist = []
	fp = open('/home/2016/sthibo6/public_html/users.txt', 'r')
	while True:
		line = fp.readline().strip('\n')
		if line.startswith(name): 
			line = fp.readline()
			line = fp.readline()
			userlist.append(line)
			line = fp.readline()
			userlist.append(line)
			fp.close()
			return userlist 
		elif not line:
			fp.close()
			return

cgitb.enable()
form = cgi.FieldStorage()
user = str(form.getvalue('currentuser'))
profile = str(form.getvalue('submit'))
print("Content-Type:text/html\n\n")
print('<head><title>%s</title></head>' % (profile))
print("<body>")
print('<h1>%s</h1>' % (profile))
info = getprofile(profile)
job = info[0]
name = info[1]
print('<h3> %s</br> %s</br> </h3>' % (job, name))
with open('/home/2016/jmerri8/public_html/status.txt', 'r') as f:
	for line in f:
		if line.startswith(profile):
			print(line + '</br>')

print('<form name="return" action ="dashboard.py" method="post">')
print('<input type = "hidden" name="currentuser" value="%s">' % (user))
print('<input type = "submit" name="submit" value="Return to Dashboard">')
print('</form>')
print('</body>')
print('</html>')
