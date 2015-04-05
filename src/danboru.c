#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

void danborusingle(char[], char[], char[]);
void danborubulk(char[], char[], char[], char[]);

void danboru(char url_orig[], char protocol[], char name[], char chapter[]){
	
	strcpy(name,strtok(NULL, "/"));
	if (strcmp(name, "posts") == 0){
	strcpy(name,strtok(NULL, "\0"));
	}
		if (isalpha(name[1]))
			danborubulk(url_orig, protocol, name, chapter);
		else
			danborusingle(url_orig, protocol, name);

return;
}

void danborusingle(char url_orig[], char protocol[], char name[]){
	printf("This is danborusingle");
return;
}

void danborubulk(char url_orig[], char protocol[], char name[], char chapter[]){

printf("This is danborubulk");
//Name	
printf("Give a name to the board: ");
scanf("%49s", name);
return;
}
