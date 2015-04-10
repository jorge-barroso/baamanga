#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <ctype.h>
#include <unistd.h>

void animeasingle(char[], char[], char[], char[], char[]);
void animeabulk(char[], char[], char[], char[]);

void animea(char url_orig[], char name[], char downdir[]){
char discr[50], chapter[4];
	strcpy(discr, strtok(NULL,"\0"));
	if(strstr(discr, "chapter") != NULL){
		animeasingle(url_orig, name, chapter, discr, downdir);
	}
	else{
		animeabulk(url_orig, name, chapter, downdir);
	}
return;
}

void animeasingle(char url_orig[], char name[], char chapter[], char discr[], char downdir[]){
	char namex[40];
	short unsigned int j;
	
    //Complex name parsing
	strcpy(namex, strtok(discr, "-"));
    while (strcmp(namex, "chapter")!= 0){
		strcat (name, namex);
		strcat (name, " ");
		strcpy(namex, strtok(NULL, "-"));
		}										//Now starts capitalizing
	for (j=0; name[j]!='\0'; j++){
		if (isalpha(name[j]) && name[j-1] == ' ')
			name[j] = toupper(name[j]);
		}
	if (isalpha(name[0]))
		name[0] = toupper(name[0]);
	
	//Chapter
	strcpy(chapter, strtok(NULL, "h"));
	j = strlen(chapter);
	chapter[j] = '\0';
	printf("Name: %s\nChapter: %s\n", name, chapter);
return;
}

void animeabulk(char url_orig[], char name[], char chapter[], char downdir[]){
return;
}
