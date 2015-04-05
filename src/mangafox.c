#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>

void mangafox(char url_orig[], char protocol[], char name[], char chapter[]){
short unsigned int j;
    strtok (NULL, "/");
    //Let's parse the name
    strcpy (name, strtok(NULL, "/"));
    	
    for (j=0; name[j] != '\0'; j++){
        if (name[j] == '_')
        name[j] = ' ';
    }
    //Now for the chapter 
    strcpy (chapter, strtok(NULL, "/"));
    if(isalpha(chapter[0])){
    	chapter[0] = '\0';
       }
    while (chapter[j] == '0'){
    	chapter[j] = '\0';
       }
printf("Name: %s\nChapter: %s\n", name, chapter);
}
