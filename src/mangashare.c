#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

void mangashare(char url_orig[], char protocol[], char name[], char chapter[]){
short unsigned int j;
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
