#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>

void mangareader(char url_orig[], char protocol[], char name[]){
    unsigned short int i;
    char chapter[4];
    //Name easy parsing
strcpy (name, strtok (NULL, "/"));
    for (i=0;name[i]!='\0';i++){
        if(name[i] == '_')
        	name[i] = ' ';
        if (isalpha(name[i]) && name[i-1] == ' ') 
        toupper (name[i]);
    }
    if (isalpha(name[0]))
        	toupper (name[i]);
    //Get the chapter 
    strcpy(chapter,strtok (NULL,"/"));
}
