#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <ctype.h>

void mcanime(char url_orig[], char protocol[], char name[]){
short unsigned int i;
strtok(NULL, "/");
strcpy(name, strtok(NULL, "."));
    for (i=0;name[i]!='\0';i++){
        if(name[i] == '_')
        	name[i] = ' ';
        if (isalpha(name[i]) && name[i-1] == ' ') 
        toupper (name[i]);
    }
	if (isalpha(name[i]) && i==0)
        	toupper (name[i]);
printf("Starting download of %s\n", name);

return;
}
