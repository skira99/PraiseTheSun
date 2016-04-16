#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	char *strlen;
	long len;
	char *strtmp;
	int i;
	
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10);
	printf("<html>\n");
	printf("<head><title>Result</title></head>\n");

	strlen = getenv("CONTENT_LENGTH");
	if(sscanf(strlen,"%ld", &len)!= 1 || strlen == NULL){
		printf("<body><p>There was an error in processing the input.</body>\n");
	}
	else{
		printf("<body><p>The length of the input was %ld\n", len);
		char input[len+5];
		char data[len+5];
		fgets(input, len+1, stdin);
		printf("<p>The input was %s\n", input);
		strcpy(data, input);
		for(i=0; i < len+1; i++){
			if((data[i] == '=') || (data[i] == '+') || (data[i] == '&')){
				data[i] = ' ';
			}
		}
		printf("<p>The parsed input is %s\n", data);
		strtmp = strtok(data," ");
		while(strtmp != NULL){
			printf("<p>The token is %s\n", strtmp);
			strtmp = strtok(NULL, " ");
		}
	}	
	printf("</body></html>");
}
