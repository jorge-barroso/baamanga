#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>
#include <unistd.h>

size_t write_data_mangareader(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void mangareader(char url_orig[], char name[], char chapter[], char downdir[]){
    short int j;
    //Name easy parsing
strcpy (name, strtok (NULL, "/"));
    for (j=0;name[j]!='\0';j++){
        if(name[j] == '_')
        	name[j] = ' ';
        if (isalpha(name[j]) && name[j-1] == ' ') 
        name[j] = toupper(name[j]);
    }
    if (isalpha(name[0]))
        	name[0] = toupper(name[0]);
    //Get the chapter 
    strcpy(chapter,strtok (NULL,"/"));
printf("Name: %s\nChapter: %s\n", name, chapter);
}
