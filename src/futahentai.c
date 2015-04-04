#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

void futahentai(char url_orig[], char protocol[], char name[]){
    short unsigned int i, length;
strtok (NULL, "-");
    //Let's parse the name
strcpy(name, strtok(NULL, "-"));
    length = strlen(name);
i = length;
name[i] = '\0';
name[i-1] = '\0';
for(i=0;i<length;i++){
 if (name[i] == '-') 
		name[i] = ' ';
}
printf("%s", name);
return;
}
