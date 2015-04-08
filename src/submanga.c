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
	if (strcmp(discr, "completa") == 0){
		submangabulk(url_orig, name, chapter, downdir);
	}
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
short int i=1;
//char url[100], p[4], file[40], file_orig[40];
bool err = 0;
//short int length = strlen(downdir);
char urldown[100] = "http://submanga.com/c";
char baseimg[] = ".jpg";
char tmpfile[] = "/tmp/.html";
short unsigned int j=0, line = 1, result=0;
unsigned int sz;
char temp[12000], p[3];
char imgurl[7];

	strcat(urldown,(strtok(strrchr(url_orig, '/'), "\0")));
	puts(urldown);
	
	while(err == 0){
		sprintf(p, "%d", i);
		strcat(strcpy(imgurl, p), baseimg);
	if(curl) {
		curl = curl_easy_init();
		fp = fopen(tmpfile, "w+");
		curl_easy_setopt(curl, CURLOPT_URL, url_orig);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_submanga); //Save
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);						//Where
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);						//No output
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);						//Autoredirect
	
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    fclose(fp);
    /* Check for errors */
    if(res != CURLE_OK){
		fprintf(stderr, "Download failed: %s\n", curl_easy_strerror(res));
		}
    /* always cleanup */
    curl_easy_cleanup(curl);
	}
	fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	
	sprintf(temp, "%d", sz);
	
	fp = fopen(tmpfile, "r");
	
	
    while(fgets(temp, sz, fp) != '\0'){
			printf("%s\n", temp);
			if (strstr(temp,urldown) != '\0'){
				printf("Resultado: %s\n", temp);/*
				fgets(temp, 32, fp);
				strcpy(imgurl, temp);
				puts(imgurl);*/
				result++;
				}
			else
		line++;
			}
			
    while(fgets(temp, sz, fp) != '\0'){
			//printf("%s\n", temp);
			if (strstr(temp,imgurl) != '\0'){
				printf("Resultado: %s\n", temp);
				result++;
				}
			else
		line++;
			}	

		printf("Downloading page %d...\n", i);
		/*strcpy(file, file_orig);
		strcpy(url,url_orig);*/
		if (result == 0);
		err = 1;
    i++, j++;
    
    if (result == 0)
		err = 1;
    }
	if (i > 2)
		printf("%s chapter %s downloaded\n", name, chapter);
	
return;
}

void submangabulk(char url_orig[], char name[], char chapter[], char downdir[]){
printf("This is submangabulk");
return;
}
