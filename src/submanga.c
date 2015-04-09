#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <ctype.h>

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
	FILE *img;
CURL *curl;
CURLcode res;
short int i=1, j=0, k=0;
bool err = 0, pgfound = 0;
char urldown[100] = "http://submanga.com/c";
char pagedown[100];
char baseimg[] = ".jpg";
char tmpfile[] = "/tmp/.html";
short unsigned int result=0;
char p[3], q[3], imgurl[7];
char html[153600];
int length;

	strcat(urldown,(strtok(strrchr(url_orig, '/'), "\0")));
	while(err == 0){
		if (i > 1)
		result = pgfound = 0;
		sprintf(p, "%d", i);
		sprintf(q, "%d", k);
		printf("%s %s\n", p, q);
		strcat(strcpy(imgurl, q), baseimg);
		puts(baseimg);
		if (j==1)
			strcat(urldown, "/");
		if (j > 1 && j < 9 ){/* "i", and then p, higher than 9 so, two digits*/
			length = strlen(urldown);
			urldown[length-1] = '\0';
		}
		if (j > 0)
			strcat(urldown, p);
		printf("EEEEEEEEEEEEEY URLDOWN IS %s AND URL_ORIG IS %s\n", urldown, url_orig);
		/* Download html page*/
	if(curl) {
		curl = curl_easy_init();
		fp = fopen(tmpfile, "w+");
		curl_easy_setopt(curl, CURLOPT_URL, url_orig);
		curl_easy_setopt(curl, CURLOPT_URL, url_orig);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_submanga); //Save
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);						//Where to save
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);						//No output
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);						//Autoredirect
	
	
    res = curl_easy_perform(curl);
    fclose(fp);
    
    if(res != CURLE_OK){
		err = 1;
		}
		
    curl_easy_cleanup(curl);
	}
	/* HERE WILL START HTML PARSING OF THE FILE */			
		
		fp = fopen(tmpfile, "r");
		/* Look for the next html page to download */
		if (i < 10){
		while (fgets(html, sizeof(html) - 1, fp) != '\0'){
			puts(html);
			if (strstr(html, urldown) != NULL){
				printf("%s\n", strstr(html, urldown));
				sscanf(strstr(html, urldown), "%30s", url_orig);
				length = strlen(url_orig);
				if (i == 1)
					url_orig[length-1] = '\0';
					printf("URL = %s\n", url_orig);
					result++;
				}
			}
			strcpy(html,"");
		}
		
		printf("%d\n", result);
		if (result == 0)
			err = 1;
		
		/* Look for the picture */
		if (i < 10 && i>1){
		while (fgets(html, sizeof(html) - 1, fp) != '\0'){
			if (strstr(html, imgurl) != NULL){
			//	if (strtok(strrchr('/'), '\0') > p){
				printf("%s\n", strstr(html, imgurl));
				sscanf(strstr(html, imgurl), "%30s", pagedown);
				length = strlen(pagedown);
				if (!isdigit(pagedown[length]))
					pagedown[length-1] = '\0';
					puts(pagedown);
					pgfound = 1;
				}
			}
			strcpy(html,"");
		}
		fclose(fp);
		
		printf("Downloading page %d...\n", i);
		printf("Downloading %s\n", url_orig);
		
		/* Now for the image */
		if (pgfound == 1){
		img = fopen(imgurl, "w+");
		if(curl) {
			printf("DOWNLOADING\n");
		curl = curl_easy_init();
		fp = fopen(tmpfile, "w+");
		curl_easy_setopt(curl, CURLOPT_URL, pagedown);
		curl_easy_setopt(curl, CURLOPT_URL, pagedown);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_submanga); //Save
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, img);						//Where to save
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);						//No output
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);					//Autoredirect
	
	
		res = curl_easy_perform(curl);
		fclose(img);
    
		if(res != CURLE_OK){
			err = 1;
				}
		
		curl_easy_cleanup(curl);
			}
		}
		i++, j++, k++;
		
	}
	if (i > 2)
		printf("%s chapter %s downloaded\n", name, chapter);

return;
}

void submangabulk(char url_orig[], char name[], char chapter[], char downdir[]){
printf("This is submangabulk");
return;
}
