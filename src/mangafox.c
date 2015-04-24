#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <unistd.h>

void namedir_check(char[], char[]);
void chapdir_check(char[], char[]);
void mangafoxsingle(char[], char[], char[], char [], char[]);
void mangafoxbulk(char[], char[], char[]);
size_t write_data();

void mangafox(char url_orig[], char name[], char downdir[]){
short int j;
char discr [6];
char chapter [5], chaptorig[5];

    strtok (NULL, "/");

    //Let's parse the name
    strcpy (name, strtok(NULL, "/"));

    for (j=0; name[j] != '\0'; j++){
        if (name[j] == '_')
        name[j] = ' ';
        if (isalpha(name[j]) && name[j-1] == ' ')
        name[j] = toupper(name[j]);
    }
    name[0] = toupper(name[0]);

    //Now for the chapter
	strcpy (discr, strtok(NULL, "/"));

    if (discr == '\0'){
		printf("This is Mangafox Bulk\n");
		mangafoxbulk(name, url_orig, downdir);
	}
	else{
		if (discr[0] != 'c') //If it's not cXXXX and it's not empty, it means that
			strcpy (chapter, strtok(NULL, "/")); //it is a chapter, but this is the volume serial name
		else
			strcpy (chapter, discr);
			strcpy (chaptorig, chapter);
		while (chapter[0] == 'c' || chapter[0] == '0')
			memmove(chapter, chapter+1, strlen(chapter));
		printf("\n	Name: %s\n	Chapter: %s", name, chapter);
		mangafoxsingle(url_orig, name, chapter, chaptorig, downdir);
	}
return;
}

void mangafoxsingle(char url_orig[], char name[], char chapter[], char chaptorig[], char downdir[]){

	FILE *fp;
	FILE *img;
CURL *curl;
CURLcode res;
short int i=1, k=0;
bool err = 0, result=0, pgfound = 0;
char urldown[9];
char pgbase[] = "http://a.mfcdn.net/store/manga/";
char tmpfile[30] = "/tmp/.html-mangafox";
char baseimg[] = ".jpg";
char html[153600], imgname[8], pageurl[200], p[4], q[4];
int length;

	strncat		    (tmpfile, name, 10);

	namedir_check	(name, downdir);
	strcat		    (strcat(downdir, "/"), name);
	chapdir_check	(chapter, downdir);
	strcat          (strcat(downdir, "/"), chapter);
	chdir		    (downdir);

	while(err == 0){
		length=strlen(url_orig);
		result = 0;
		pgfound = 0;
		sprintf(p, "%d", i+1);
		sprintf(q, "%.3d", k+1);
		strcat(strcpy(urldown, p), ".html");
		strcat(strcpy(imgname, q), baseimg);

		/* Download html page*/
		curl = curl_easy_init();
	if(curl) {
		fp = fopen(tmpfile, "w+");
		curl_easy_setopt(curl, CURLOPT_URL, url_orig);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); 	//Save
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);				//Where to save
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);			//Autoredirect
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

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
			if (i==11)	//length + 1
			length++;
			if (i==101)	//You never know XD
			length++;
			while(url_orig[length-1] != '/'){
			url_orig[length-1] = '\0';
			length--;
			}
			strcat (url_orig, urldown);
			result++;
		}
	}
	rewind(fp);

	if (result == 0)
		err = 1;

	/* HERE WE GET THE PAGE URL */

	while (fgets(html, sizeof(html) - 1, fp) != '\0'){
		if (strstr(html, pgbase) != NULL && strstr(html, "compressed") != NULL && pgfound < 1) {
			strcpy (pageurl, strtok(strstr(html, pgbase), "\""));
			pgfound++;
		}
	}

	fclose(fp);

	if (pgfound == 1){
		printf("\n\n\nDownloading page %d...\n", i);
		img = fopen(imgname, "w+");
		if(curl) {
			curl = curl_easy_init();
			curl_easy_setopt(curl, CURLOPT_URL, pageurl);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);          //Save
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

void mangafoxbulk(char name[], char url_orig[], char downdir[]){

return;
}
