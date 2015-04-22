#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>
#include <unistd.h>

void namedir_check(char[], char[]);
void chapdir_check(char[], char[]);
void mangareadersingle(char[], char[], char[], char[]);
void mangareaderbulk(char[], char[], char[], char[]);
size_t write_data();

void mangareader(char url_orig[], char name[], char downdir[]){
    short j, len;
    char chapter[4];
    //Name easy parsing
strtok(NULL, "/");
strcpy (name, strtok (NULL, "/"));
	
	for (j=0;name[j]!='\0';j++){
        if(name[j] == '-')
        	name[j] = ' ';
        if (isalpha(name[j]) && name[j-1] == ' ') 
        name[j] = toupper(name[j]);
    }
    if (isalpha(name[0]))
        	name[0] = toupper(name[0]);
        	
	len = strlen(name);
	if (name[len-5] == '.'){
	strtok (name, ".");
	printf("Name: %s\n", name);
	mangareaderbulk(url_orig, name, chapter, downdir);
	}
	else{	
    strcpy(chapter,strtok (NULL,"."));
    strcpy(chapter, strrchr(chapter, '-') + 1);
	printf("\n	Name: %s\n	Chapter: %s", name, chapter);
	mangareadersingle(url_orig, name, chapter, downdir);
	}
}

void mangareadersingle(char url_orig[], char name[], char chapter[], char downdir[]){
	
	FILE *fp;
	FILE *img;
CURL *curl;
CURLcode res;
bool err = 0;
char urldown[50];
	namedir_check(name, downdir);
	strcat(strcat(downdir, "/"), name);
	chapdir_check(chapter, downdir);
	strcat(strcat(downdir, "/"), chapter);
	chdir(downdir);
	
	strcpy(url_orig, urldown);
	strtok(urldown, "/");
	strtok(NULL, "/");
	strcpy(urldown, strtok(NULL, "/"));
	while (urldown[strlen (urldown) -1] != '-')
	urldown[strlen (urldown) -1] = '\0';
	urldown[strlen (urldown) -1] = '\0';
	puts(urldown);
	
	while (err == 0){}
		
	
return;
}

void mangareaderbulk(char url_orig[], char name[], char chapter[], char downdir[]){

return;
}
