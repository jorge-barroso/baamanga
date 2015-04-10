#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>

void zerochansingle(char[], char[], char[]);
void zerochanbulk(char[], char[], char[]);

void zerochan(char url_orig[], char name[], char downdir[]){
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
		zerochanbulk(url_orig, name, downdir);
	}
	else
		printf("Please, give a name for the file you are going to download");
		scanf("%49s", name);
		 zerochansingle(url_orig, name, downdir);
}

void zerochansingle(char url_orig[], char name[], char downdir[]){
printf("This is zerochansingle");
return;
}

void zerochanbulk(char url_orig[], char name[], char downdir[]){

//short int pages[4];

printf("This is zerochanbulk");
return;
}
