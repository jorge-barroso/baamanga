#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

void submangasingle(char[], char[], char[], char[]);
void submangabulk(char[], char[], char[], char[]);

void submanga(char url_orig[], char protocol[], char name[], char chapter[]){
	int j;
	char discr[10];
	
	// Parse name
	strcpy(name, strtok(NULL, "/"));

	for(j=0;name[j]!='\0'; j++){
		if (name[j] == '_'){
			name[j] = ' ';
		}
	}
	strcpy(discr, strtok(NULL, "/"));
	if (strcmp(discr, "completa") == 0)
		submangabulk(url_orig, protocol, name, chapter);
	else{
		strcpy(chapter,discr);
		printf("Name: %s\nChapter: %s\n", name, chapter);
		submangasingle(url_orig, protocol, name, chapter);
	}
  return;
}

void submangasingle(char url_orig[], char protocol[], char name[], char chapter[]){
printf("This is submangasingle");
return;
}

void submangabulk(char url_orig[], char protocol[], char name[], char chapter[]){
printf("This is submangabulk");
return;
}
