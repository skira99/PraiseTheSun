#include <stdio.h>

int main(void){
	FILE *pointer;
	char line[1000];
	pointer = fopen("../error.html", "r");
	fgets(line, 999, pointer);
	printf("%s%c%c\n" ,"Content-Type:text/html;charset=iso-8859-1", 13, 10);
	while(!feof(pointer)){
		puts(line);
		fgets(line, 999, pointer);}
	fclose(pointer);
	return 0;
}
