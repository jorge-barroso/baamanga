#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <stdbool.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(){

FILE *fp;
CURL *curl;
CURLcode res;
char url_orig[100] = "http://submanga.com/c/242013";
char file[40] = "/tmp/.html";
short int result, i = 1, line = 1, length = strlen(url_orig), buff;
char p[3], temp[32], url[100];
bool err = 0;

	while( err == 0){
	curl = curl_easy_init();
	if(curl) {
	fp = fopen (file, "w+");
		curl_easy_setopt(curl, CURLOPT_URL, url_orig);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        //curl_easy_setopt (curl, CURLOPT_VERBOSE, 1L);
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    fclose(fp);
    		
	/* Check for errors */
    if(res != CURLE_OK){
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
	}
    /* always cleanup */
    curl_easy_cleanup(curl);
    
    
    fp = fopen(file, "r");
    if (i<10){
		strcat(url_orig, "/");
		sprintf(p, "%d", i);
		strcat(url_orig,p);
		printf("%s\n", url_orig);
		}
	if (i>10){
		strcat(url_orig, "/");
		sprintf(p, "%d", i);
		strcat(url_orig,p);
		printf("%s\n", url_orig);
		printf("%s\n", url_orig);
		}
		while(fgets(temp, 300, fp) != '\0'){
			//printf("%s\n", temp);
			if (strstr(temp,url_orig) != '\0'){
				printf("Resultado: %s\n", temp);
				result++;
				}
		line++;
			}
		if (result == 0);
		err = 1;
		i++;
		url_orig[length] = '\0';
		}
			
return 0;
}
