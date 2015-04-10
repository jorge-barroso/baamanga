#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>

void mangashare(char url_orig[], char name[], char downdir[]){
short unsigned int j;
char chapter[4];
	//Name parse
    strcpy (name, strtok (NULL, "/"));
    for(j=0;name[j]!='\0';j++){
        if (name[j] == '-')
        name[j] = ' ';
    }
    //Parse chapter
    strtok(NULL, "-");
    strcpy (chapter, strtok (NULL, "/"));

printf("Name: %s\nChapter: %s\n", name, chapter);
}
