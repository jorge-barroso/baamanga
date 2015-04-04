#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <ctype.h>

void animea(char url_orig[], char protocol[], char name[]){
	char namex[40];
    //Complex name parsing 
	strcpy (namex, strtok(NULL, "."));
    while (strcmp(namex, "chapter")!= 0){
        if (strcmp(name, "") == 0)
        strcpy(name, namex);
        else{
            name = name + ' ' + namex;
        	}
        strcpy(namex, strtok(NULL, "-"));
        }
return;
}
