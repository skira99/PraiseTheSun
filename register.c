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

//	char* input = "uname=longassusernametobetest&name=Samuel+Thibodeau&job=Student+at+McGill&pass=bonbon&pass2=bonbon&submit=input";
	
	int i = 0;
	while(input[i]!= '&')
		i++;
	char user[i-4];

	int j = i+1;
	while(input[j]!= '&')
		j++;
	char name[j-i-1-3];

	int k = j+1;
	while(input[k]!= '&')
		k++;
	char job[k-j-1-4];

	int l = k+1;
	while(input[l]!= '&')
		l++;
	char pass[l-k-1-3];

	int m = l+1;
	while(input[m]!= '&')
		m++;
	char pass2[m-l-1-4];

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
	for(a=i+6;a<j+1;a++){
		if(a == j)
			name[a-i-6] = '\0';
		else if (input[a] == '+')
			name[a-i-6] = ' ';
		else
			name[a-i-6] = input[a];	
	}
	for(a=j+5;a<k+1;a++){
		if(a == k)
			job[a-j-5] = '\0';
		else if (input[a] == '+')
			job[a-j-5] = ' ';
		else

			job[a-j-5] = input[a];	
	}	
	for(a=k+6;a<l+1;a++){
		if(a == l)
			pass[a-k-6] = '\0';
		else if (input[a] == '+')
			pass[a-k-6] = ' ';
		else
			pass[a-k-6] = input[a];	
	}
	for(a=l+7;a<m+1;a++){
		if(a == m)
			pass2[a-l-7] = '\0';
		else if (input[a] == '+')
			pass2[a-l-7] = ' ';
		else
			pass2[a-l-7] = input[a];	
	}

//	printf("%s\n", user);
//	printf("%s\n", pass);
//	printf("%s\n", job);
//	printf("%s\n", name);

	pntr = fopen("users.txt", "r+wt");
	
	if (pntr == NULL){
		printf("error in opening file\n");
		return 0;
	}
	
	fgets(line, 299, pntr);
	line[strcspn(line, "\n")] = '\0';
	while( ( strcmp(line,user) != 0 ) && (!feof(pntr)) ){
		fgets(line,299,pntr);
		line[strcspn(line, "\n")] = '\0';
	}

	if( (strcmp(line,user) == 0) || (strcmp(pass,pass2) != 0) ){
		fclose(pntr);
		FILE *html;
		html = fopen("error.html", "r");
		fgets(line, 299, html);
		printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10);
		while(!feof(html)){
			printf("%s", line);
			fgets(line,299,html);
		}
		fclose(html);
	}
	else{
		fputs(user, pntr);
		fputs("\n", pntr);
		fputs(pass, pntr);
		fputs("\n", pntr);
		fputs(name, pntr);
		fputs("\n", pntr);
		fputs(job, pntr);
		fputs("\n", pntr);

		fclose(pntr);

		FILE *html;
		html = fopen("successreg.html", "r");
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
