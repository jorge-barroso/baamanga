#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>

size_t write_data_futahentai(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void futahentai(char url_orig[], char name[], char chapter[], char downdir[]){
short unsigned int j;
	strtok (NULL, "-");
    //Let's parse the name
	strcpy(name, strtok(NULL, "-"));
	for(j=0;name[j]!='\0';j++){
		if (name[j] == '_') 
			name[j] = ' ';
}
	//Parsing chapter
	strcpy(chapter, strtok(NULL, "."));
	
	printf("Name: %s\nChapter: %s\n", name, chapter);
return;
}
