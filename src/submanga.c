#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <stdbool.h>

void submangasingle(char[], char[], char[], char[]);
void submangabulk(char[], char[], char[], char[]);

size_t write_data_submanga(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void submanga(char url_orig[], char name[], char chapter[], char downdir[]){
	int j;
	char discr[10];
	
	// Parse name
	strcpy(name, strtok(NULL, "/"));

	for(j=0;name[j]!='\0'; j++){
		if (name[j] == '_'){
			name[j] = ' ';
		}
	}
	strcpy(discr, strtok(NULL, "/"));
	if (strcmp(discr, "completa") == 0)
		submangabulk(url_orig, name, chapter, downdir);
	else{
		strcpy(chapter,discr);
		printf("Name: %s\nChapter: %s\n", name, chapter);
		submangasingle(url_orig, name, chapter, downdir);
	}
  return;
}

void submangasingle(char url_orig[], char name[], char chapter[], char downdir[]){
	FILE *fp;
CURL *curl;
CURLcode res;
int sz;
short int i=1;
char url[100], p[4], file[40], file_orig[40];
bool err = 0;
short int length = strlen(downdir);

	//stat(downdir);
	if (downdir[length] != '/')
		strcat(downdir, "/");
	strcat(downdir, name);
	strcat(downdir, "/");
	strcpy(file, downdir);
	strcat(file, "page ");
	strcpy(url, url_orig);
	
	curl = curl_easy_init();
	
	if(curl) {
	while(err == 0){
		sprintf(p, "%d", i);
		printf("%s", p);
		strcat (file, p);
		strcat (file, ".jpg");
		fp = fopen(file, "w+");
		strcat(url, p);
		strcat(url, ".jpg");
		printf("%s\n",url);
		printf("%s\n",file);
		curl_easy_setopt(curl, CURLOPT_URL, url );
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_submanga);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    fclose(fp);
    fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);
	if (sz < 500){
		err=1;
		remove (file);
	}
	if (err == 0){
		printf("Page %d downloaded", i);
		strcpy(file, file_orig);
		strcpy(url,url_orig);
		i++;
    }
    /* Check for errors */
    if(res != CURLE_OK){
		fprintf(stderr, "Download failed: %s\n", curl_easy_strerror(res));
		}
	}
	if (i > 1)
		printf("%s chapter %s downloaded", name, chapter);
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
return;
}

void submangabulk(char url_orig[], char name[], char chapter[], char downdir[]){
printf("This is submangabulk");
return;
}
