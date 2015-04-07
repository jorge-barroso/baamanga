#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>
#include <unistd.h>

size_t write_data_mangafox(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void mangafox(char url_orig[], char name[], char chapter[], char downdir[]){
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
