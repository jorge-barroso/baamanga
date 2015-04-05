#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

void zerochansingle(char[], char[], char[]);
void zerochanbulk(char[], char[], char[], char[]);

void zerochan(char url_orig[], char protocol[], char name[], char chapter[]){
short unsigned int j;
char discr;

	strcpy(name, strtok(NULL, "\0"));
	
	for(j=0;name[j]!='\0';j++){
		if (name[j] == '+' || isalpha(name[j]))
		discr = 1;
	}
	if (discr == 1){
		for(j=0;name[j]!='\0';j++){
			if (name[j] == '+' && name[j-1] != '\0'){
				name[j] = ' ';
				}
			}
		zerochanbulk(url_orig, protocol, name, chapter);
	}
	else
		printf("Please, give a name for the file you are going to download");
		scanf("%49s", name);
		 zerochansingle(url_orig, protocol, name);
}

void zerochansingle(char url_orig[], char protocol[], char name[]){
printf("This is zerochansingle");
return;
}

void zerochanbulk(char url_orig[], char protocol[], char name[], char chapter[]){
printf("This is zerochanbulk");
return;
}
