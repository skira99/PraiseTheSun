#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char buffer[128];
char user[32];

typedef struct FRIEND
{
	char name[32];
}FRIEND;

/*allows for easier allocation of friend array*/

void getusername()
{
	int maxlen = atoi(getenv("CONTENT_LENGTH"));
	fgets(buffer, maxlen+1, stdin);
	char *result = strstr(buffer, "=");
	int pos1 = result - buffer + 1;
	char *pch2 = strstr(result, "&");
	int pos2 = pch2 - buffer;
	int length = pos2 - pos1;
	memset(user, '\0', 32);
	strncpy(user, buffer+pos1, length);
	user[length+1] = '\0';
}

int exists(const char *filename)
{
	FILE *fp;
	fp = fopen(filename, "r");
	if(fp == NULL)
	{
		return 0;
	}
	else 
	{	
		fclose(fp);
		return 1;
	}
}

int setfriends(FRIEND friends[], const char *user)  /* returns # of friends, -1 if error */
{
	if(exists("friends.txt") == 0)
	{
		return; 
	}
	else
	{
		FILE *fp = fopen("/home/2016/sthibo6/public_html/friends.txt", "r");
		int found = 0;
		char line[1024];
		fgets(line, 999, fp);
		while(line != NULL)
		{
			char *token;
			token = strtok(line, " ");
			if(strcmp(token, user) == 0)
			{
				found = 1;
				break;
			}		
			else
			{
				fgets(line, 999, fp);
			}
		}
		int i = 0;
		if(found == 1)
		{
			char *nexttoken = strtok(NULL, " \n");
			while(nexttoken != NULL)
			{         
				strcpy(friends[i].name, nexttoken);
				++i;
                                nexttoken = strtok(NULL, "  \n");
			}
			return i;
		}
		else return -1;
	}
}

void printheader()
{
	printf("Content-Type:text/html\n\n");
	printf("<html>");
	printf("<head><title>See A Friend</title></head>");
	printf("<body>");
	printf("<h3>See a Friend!</h3>");
}

int main(int argc, char **argv)
{
	getusername();  
	FRIEND userfriends[128];
	int numfriends = setfriends(userfriends, user);
	int i;
	printheader();
	for(i = 0; i < numfriends; ++i)
	{
		printf("<form name=\"seefriend%d\" action=\"profile.py\" method=\"post\">", i);
		printf("<input type=\"hidden\" name=\"currentuser\" value=%s>", user);
		printf("<input type=\"submit\" name=\"submit\" value=\"%s\">", userfriends[i].name);
		printf("</form>");
	}
	printf("<form name=\"return\" action=\"dashboard.py\" method=\"post\">");
	printf("<input type=\"hidden\" name=\"currentuser\" value=%s>", user);
	printf("<input type=\"submit\" name=\"back\" value=\"Return to Dashboard\">");
        printf("</body> </html>");
	return 0;
}

