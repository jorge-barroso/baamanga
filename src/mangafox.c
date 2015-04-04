#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>

void mangafox(char url_orig[], char protocol[], char name[]){
short unsigned int i, length;
    char chapter[4];
    strtok (NULL, "/");
    //Let's parse the name
    strcpy (name, strtok(NULL, "/"));
    	
    for (i=0; name[i] != '\0'; i++){
        if (name[i] == '_')
        name[i] = ' ';
    }
    //Now for the chapter 
    strcpy (chapter, strtok(NULL, "/"));
    if(isalpha(chapter[0])){
    	chapter[0] = '\0';
       }
    while (chapter[i] == '0'){
    	chapter[i] = '\0';
       }
}
