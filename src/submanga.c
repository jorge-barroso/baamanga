#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

void submanga(char url_orig[], char protocol[], char name[]){
	int j=0;
	strcpy(name, strtok(NULL, "/"));

	for(;name[j]!='\0'; j++){
		if (name[j] == '_'){
			name[j] = ' ';
		}
	}
		
	printf("Starting download of %s\n", name);
  return;
}
