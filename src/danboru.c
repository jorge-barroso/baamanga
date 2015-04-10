#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>

void danborudirect(char[], char[], char[]);
void danborusingle(char[], char[], char[]);
void danborubulk(char[], char[], char[], char[]);

void danboru(char url_orig[], char name[], char downdir[]){
	
	char chapter[3];
	
	strcpy(name,strtok(NULL, "/"));
	
	if (strcmp(name, "posts") == 0){
	strcpy(name,strtok(NULL, "\0"));
		if (isalpha(name[1]))
				danborubulk(url_orig, name, chapter, downdir);
			else{
				danborusingle(url_orig, name, downdir);
			}
		}
	else if (strcmp(name, "data") == 0){
	danborudirect(url_orig, name, downdir);
	}
	
		

return;
}

void danborudirect(char url_orig[], char name[], char downdir[]){

printf("Select a name for your downloaded file: ");
scanf("%s", name);
FILE *fp;

	fp = fopen(name, "w+");

	CURL *curl;
	CURLcode res;
	
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url_orig);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	
		chdir(downdir);
		res = curl_easy_perform(curl);
		
		if(res != CURLE_OK)
		fprintf(stderr, "Download failed: %s\n", curl_easy_strerror(res));
	
		/* Cleanup */ 
		curl_easy_cleanup(curl);
	}
	fclose(fp);
return;
}

void danborusingle(char url_orig[], char name[], char downdir[]){

printf("Select a name for your downloaded file");
scanf("%s", name);
FILE *fp;

	fp = fopen(name, "w+");

	CURL *curl;
	CURLcode res;
	
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url_orig);
		/* example.com is redirected, so we tell libcurl to follow redirection */ 
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	
		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);
		/* Check for errors */ 
		if(res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
	
		/* Cleanup */ 
		curl_easy_cleanup(curl);
	}
	fclose(fp);
return;
}

void danborubulk(char url_orig[], char name[], char chapter[], char downdir[]){

printf("This is danborubulk");
//Name	
printf("Give a name to the board: ");
scanf("%49s", name);
return;
}
