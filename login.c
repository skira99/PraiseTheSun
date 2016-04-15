#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv){
	FILE *pntr;
	char line[300];
	char *strlen;
	long inlen;

	strlen = getenv("CONTENT_LENGTH");
	if( (sscanf(strlen, "%ld", &inlen)!=1) || (strlen == NULL)){
		printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10);
		printf("<html>\n");
		printf("<head><title>Error</title></head><body>There was an error processing the input, please try again.</body>\n");
		printf("</html>\n");
	}
	else{

	char input[inlen+20];
	fgets(input, inlen+1, stdin);

//	char* input = "uname=skira99&pass=bonbon&login=submit";
	
	int i = 0;
	while(input[i]!= '&')
		i++;
	char user[i-4];

	int j = i+1;
	while(input[j]!= '&')
		j++;
	char pass[j-i-1-4];

	int a;
	for(a=6; a<i+2;a++){
		if(input[a] == '&'){
			user[a-6] = '\0';
		}
		else if (input[a] == '+'){
			user[a-6] = ' ';
		}
		else{
			user[a-6] = input[a];
		}
	}
	for(a=i+6;a<j+2;a++){
		if(input[a] == '&')
			pass[a-i-6] = '\0';
		else if (input[a] == '+')
			pass[a-i-6] = ' ';
		else
			pass[a-i-6] = input[a];	
	}

//	printf("%s\n", user);
//	printf("%s\n", pass);

	pntr = fopen("users.txt", "r");
	
	if (pntr == NULL){
		printf("error in opening file\n");
		return 0;
	}
	
	fgets(line, 299, pntr);
	line[strcspn(line, "\n")] = '\0';
	while( !( strcmp(line,user) == 0 ) && (!feof(pntr)) ){
		fgets(line,299,pntr);
		line[strcspn(line, "\n")] = '\0';
	}

	if( (strcmp(line,user) == 0) ){
	
		fgets(line,299,pntr);
		line[strcspn(line, "\n")] = '\0';	
		
		if(strcmp(line,pass) == 0){
	
			fclose(pntr);
	
			FILE *html;
			html = fopen("successlog.html", "r");
			fgets(line, 299, html);
			printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10);
			int y=1;
				
			while(!feof(html)){
				if(y == 55){
					printf("%s%s%s\n", "<input type=\"hidden\" name=\"currentuser\" value=\"", user, "\">");
				}
				printf("%s", line);
				fgets(line,299,html);
				y++;
				}
	
			fclose(html);
		}
	
		else{
			fclose(pntr);

			FILE *html;
			html = fopen("errorlog.html", "r");
			fgets(line, 299, html);
			printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10);
			
			while(!feof(html)){
				printf("%s", line);
				fgets(line,299,html);
			}

			fclose(html);
		}
	}
	else{
		fclose(pntr);

		FILE *html;
		html = fopen("errorlog.html", "r");
		fgets(line, 299, html);
		printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10);
	
		while(!feof(html)){
			printf("%s", line);
			fgets(line,299,html);
		}

		fclose(html);
	}
	return 0;
}
}
