#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

void mangaheresingle(char[], char[], char[], char[]);
void mangaherebulk(char[], char[], char[], char[]);

void mangahere(char url_orig[], char name[], char downdir[]){
	int j;
	char chapter[4];
	
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
