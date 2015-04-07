#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>

void mangaheresingle(char[], char[], char[], char[]);
void mangaherebulk(char[], char[], char[], char[]);

size_t write_data_mangahere(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void mangahere(char url_orig[], char name[], char chapter[], char downdir[]){
	int j;
	
	strtok(NULL, "/");
	// Parse name
	strcpy(name, strtok(NULL, "/"));

	for(j=0;name[j]!='\0'; j++){
		if (name[j] == '_'){
			name[j] = ' ';
		}
		if (isalpha(name[j]) && name[j-1] == ' ')
			name[j] = toupper(name[j]);
	}
	if (isalpha(name[0]))
		name[0] = toupper(name[0]);
		
	strcpy(chapter, strtok(NULL,"/"));
	if (strcmp(chapter, "\0") == 0)
		mangaherebulk(url_orig, name, chapter, downdir);
	else{
		strcpy(chapter, strtok(NULL,"c"));
		mangaheresingle(url_orig, name, chapter, downdir);
	}
		printf("Name: %s\nChapter: %s\n", name, chapter);
return;
}


void mangaheresingle(char url_orig[], char name[], char chapter[], char downdir[]){
printf("This is mangaheresingle");
return;
}

void mangaherebulk(char url_orig[], char name[], char chapter[], char downdir[]){
printf("This is mangaherebulk");
return;
}
