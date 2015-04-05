#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

void futahentai(char url_orig[], char protocol[], char name[], char chapter[]){
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
