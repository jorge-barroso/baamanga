/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2013, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(void){
FILE *fp;
CURL *curl;
CURLcode res;
int sz;
short int i=1;
char url[100] = "http://img.submanga.com/pages/3/242/242082219/";
char url_orig[100];
char p[4];
char file[40] = "/home/jorge/pagina";
char file_orig[40] = "/home/jorge/pagina";
int err = 0;
	strcpy(url_orig, url);
	
	curl = curl_easy_init();
	
	if(curl) {
	while(err == 0){
		sprintf(p, "%d", i);
		printf("%s", p);
		strcat (file, " ");
		strcat (file, p);
		strcat (file, ".jpg");
		fp = fopen(file, "w+");
		strcat(url, p);
		strcat(url, ".jpg");
		printf("%s\n",url);
		printf("%s\n",file);
		curl_easy_setopt(curl, CURLOPT_URL, url );
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        //curl_easy_setopt (curl, CURLOPT_VERBOSE, 1L);
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    fclose(fp);
    fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);
	if (sz == 177){
		err=1;
		remove (file);
	}
		
    strcpy(file, file_orig);
    strcpy(url,url_orig);
    i++;
    
    /* Check for errors */
    if(res != CURLE_OK){
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
	}
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}
