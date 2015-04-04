#include <stdio.h>
#include <string.h>
//#include <curl/curl.h>

void mangashare(char url_orig[], char protocol[], char name[]){
short unsigned int i;
    char chapter[13];
    strcpy (name, strtok (NULL, "/"));
    for(i=0;name[i]!='\0';i++){
        if (name[i] == '-')
        name[i] = ' ';
    }
    //Parse chapter
    strtok(NULL, "-");
    strcpy (chapter, strtok (NULL, "/"));
    
}
