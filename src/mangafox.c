#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <unistd.h>

void namedir_check(char[], char[]);
void chapdir_check(char[], char[]);
void mangafoxsingle(char[], char[], char[], char [], char []);
void mangafoxbulk(char[], char[], char[], char[]);

void mangafox(char url_orig[], char name[], char downdir[]){
short int j;
char nameorig[80];
char discr [6];
char chapter [5];
    strtok (NULL, "/");
    
    //Let's parse the name
    strcpy (nameorig, strtok(NULL, "/"));
    strcpy (name, nameorig);
    
    for (j=0; name[j] != '\0'; j++){
        if (name[j] == '_')
        name[j] = ' ';
        if (isalpha(name[j]) && name[j-1] == ' ')
        name[j] = toupper(name[j]);
    }
    name[0] = toupper(name[0]);
    
    //Now for the chapter
	strcpy (discr, strtok(NULL, "/"));
    if (discr[0] != 'c' && discr[0] != '\0')
		strcpy (discr, strtok(NULL, "/"));
		puts(name);
    if (discr == '\0'){
		printf("This is Mangafox Bulk\n");
		mangafoxbulk(name, nameorig, url_orig, downdir);
	}
	else{
		printf("This is Mangafox Single\n");
		strcpy (chapter, discr);
		while (chapter[0] == 'c' || chapter[0] == '0')
			memmove(chapter, chapter+1, strlen(chapter));
		printf("Name: %s\nChapter: %s\n", name, chapter);
		mangafoxsingle(url_orig, name, nameorig, chapter,downdir);
	}
return;
}

void mangafoxsingle(char url_orig[], char name[], char nameorig[], char chapter[], char downdir[]){
	
	FILE *fp;
	FILE *img;
CURL *curl;
CURLcode res;
short int i=1, k=0;
bool err = 0, pgfound = 0, mode = 0;
char urldown[50] = "http://mangafox.me/manga/";
char pageurl[60];
char pgbaseone[] = "http://a.mfcdn.net/store/manga/";
char tmpfile[] = "/tmp/.html";
short unsigned int result=0;
char p[3], q[3], imgurl[7], baseimg[] = ".jpg";
char html[153600];
int length;
	
	namedir_check(name, downdir);
	strcat(strcat(downdir, "/"), name);
	chapdir_check(chapter, downdir);
	strcat(strcat(downdir, "/"), chapter);
	chdir(downdir);
	strcat(urldown,(strtok(strrchr(url_orig, '/') +1, "\0")));
	puts(urldown);
	
	while(err == 0){
		result = 0;
		pgfound = 0;
		sprintf(p, "%d", i);
		sprintf(q, "%d", k);
		strcat(strcpy(imgurl, q), baseimg);
		if (k==1)
			strcat(urldown, "/");
		if (k > 1){/* "i", and then p, higher than 9 so, two digits*/
			length = strlen(urldown);
			urldown[length-1] = '\0';
		}
		if (k > 9)
			urldown[length-2] = '\0';
		if (k > 0)
			strcat(urldown, p);
		/* Download html page*/
		curl = curl_easy_init();
	if(curl) {
		fp = fopen(tmpfile, "w+");
		curl_easy_setopt(curl, CURLOPT_URL, url_orig);
		curl_easy_setopt(curl, CURLOPT_URL, url_orig);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); //Save
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);						//Where to save
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);					//Autoredirect
	
	
    res = curl_easy_perform(curl);
    fclose(fp);
    
    if(res != CURLE_OK){
		err = 1;
		}
		
    curl_easy_cleanup(curl);
	}
	/* HERE STARTS HTML PARSING OF THE FILE */			
		
		fp = fopen(tmpfile, "r");
		
		/* Look for the next html page to download */
		
		while (fgets(html, sizeof(html) - 1, fp) != '\0'){
			if (strstr(html, urldown) != NULL){
				if (i < 10)
				sscanf(strstr(html, urldown), "%30s", url_orig);
				else
				sscanf(strstr(html, urldown), "%31s", url_orig);
				if (i == 1){
					length = strlen(url_orig);
					url_orig[length-1] = '\0';
					}
					result++;
				}
			}
		
		rewind(fp);
		
		if (result == 0)
			err = 1;
		
		/* HERE WE GET THE PAGE URL */
		
		if (i>1){
			if (mode == 0){
				while (fgets(html, sizeof(html) - 1, fp) != '\0'){
					if (strstr(html, pgbaseone) != NULL){
						if (i < 11)
						strncpy(pageurl, strstr(html, pgbaseone), 47 + sizeof(chapter));
						else
						strncpy(pageurl, strstr(html, pgbaseone), 48 + sizeof(chapter));
							pgfound = 1;
						}
					}
				if (pgfound==0)
					mode = 1;
			}
		/*
			else if (mode == 1){
				while (fgets(html, sizeof(html) - 1, fp) != '\0'){
					if (strstr(html, pgbasetwo) != NULL){
						if (i < 11)
						strncpy(pageurl, strstr(html, pgbaseone), 47 + sizeof(chapter));
						else
						strncpy(pageurl, strstr(html, pgbaseone), 48 + sizeof(chapter));
							pgfound = 1;
						}
					}
				}*/
			}
		
		fclose(fp);
		
		if (i > 1)
		printf("\n\n\nDownloading page %d...\n", k);
		/* Now for the image */
		if (pgfound == 1){
		img = fopen(imgurl, "w+");
		if(curl) {
		curl = curl_easy_init();
		fp = fopen(tmpfile, "w+");
		curl_easy_setopt(curl, CURLOPT_URL, pageurl);
		curl_easy_setopt(curl, CURLOPT_URL, pageurl);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); //Save
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
		i++, k++;
		
	}
	if (i > 2)
		printf("\n\n%s chapter %s downloaded\n", name, chapter);

return;
}

void mangafoxbulk(char name[], char nameorig [], char url_orig[], char downdir[]){

return;
}
