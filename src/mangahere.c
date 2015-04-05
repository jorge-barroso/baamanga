#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

void mangaheresingle(char[], char[], char[], char[]);
void mangaherebulk(char[], char[], char[], char[]);

void mangahere(char url_orig[], char protocol[], char name[], char chapter[]){
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
		mangaherebulk(url_orig, protocol, name, chapter);
	else{
		strcpy(chapter, strtok(NULL,"c"));
		mangaheresingle(url_orig, protocol, name, chapter);
	}
		printf("Name: %s\nChapter: %s\n", name, chapter);
return;
}


void mangaheresingle(char url_orig[], char protocol[], char name[], char chapter[]){
printf("This is mangaheresingle");
return;
}

void mangaherebulk(char url_orig[], char protocol[], char name[], char chapter[]){
printf("This is mangaherebulk");
return;
}
