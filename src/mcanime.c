#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <ctype.h>

void mcanime(char url_orig[], char protocol[], char name[]){

strtok(NULL, "/");
strcpy(name, strtok(NULL, "/"));
name[0]=toupper(name[0]);
printf("Starting download of %s\n", name);

return;
}
