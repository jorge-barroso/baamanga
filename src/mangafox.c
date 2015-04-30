#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <unistd.h>

void namedir_check(char[], char[]);
void chapdir_check(char[], char[]);
void mangafoxsingle(char[], char[], char[], char [], char[]);
void mangafoxbulk(char[], char[], char[], char[]);
size_t write_data();

void mangafox(char url_orig[], char name[], char downdir[]){
short int l=0, foxlash;
char discr [6];
char chapter [5], chaptorig[5], nameorig[80];
bool foxmode;
    while(url_orig[l] != '\0'){
        if (url_orig[l] == '/')
            foxlash++;
        l++;
    }
    if (foxlash < 6)
        foxmode=0;
    if (foxlash >= 6)
        foxmode=1;

    strtok (NULL, "/");

    //Let's parse the name
    if (foxmode==0)
        strcpy (name, strrchr(url_orig, '/')+1);
    else if (foxmode==1)
        strcpy (name, strtok(NULL, "/"));
    strcpy(nameorig, name);

    for (l=0; name[l] != '\0'; l++){
        if (name[l] == '_')
        name[l] = ' ';
        if (isalpha(name[l]) && name[l-1] == ' ')
        name[l] = toupper(name[l]);
    }
    name[0] = toupper(name[0]);

    if(foxmode == 0){
        printf("\n	Name: %s", name);
		mangafoxbulk(name, nameorig, url_orig, downdir);
	}
	else{
        //Now for the chapter
        strcpy (discr, strtok(NULL, "/"));
		if (discr[0] != 'c')                        //If it's not cXXXX and it's not empty, it means that
			strcpy (chapter, strtok(NULL, "/"));    //it is a chapter, but this is the volume serial name
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

void mangafoxbulk(char name[], char nameorig[], char url_orig[], char downdir[]){
    FILE *bf;
CURL *pcurl;
CURLcode pre;
char p[4], blkhtml[153600], chapter[5]="c", path[]="http://mangafox.me/manga/";
char blktmpfile[]="/tmp/.baamanga-bulk-mangafox";
short foxchapters=0, i, z;
char yesno;
bool found=0;

    strcat(path,nameorig);

    pcurl = curl_easy_init();
		bf = fopen(blktmpfile, "w+");
		curl_easy_setopt(pcurl, CURLOPT_URL, url_orig);
		curl_easy_setopt(pcurl, CURLOPT_WRITEFUNCTION, write_data); 	//Save
		curl_easy_setopt(pcurl, CURLOPT_WRITEDATA, bf);				    //Where to save
		curl_easy_setopt(pcurl, CURLOPT_FOLLOWLOCATION, 1L);			//Autoredirect
		curl_easy_setopt(pcurl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

		pre = curl_easy_perform(pcurl);
		fclose(bf);

		if(pre!= CURLE_OK){
			printf("\nUnknown URL\n");
			}

		curl_easy_cleanup(pcurl);

		bf = fopen(blktmpfile, "r");
		while (fgets(blkhtml, sizeof(blkhtml) -1, bf) != '\0'){
                if (strstr(blkhtml, nameorig) != '\0' && strstr(blkhtml, "1.html") != '\0'  ){
                    foxchapters++;
                }
		}
		rewind(bf);

    //Ask for the first chapter to download for. Take 1 if not specified
    printf("\nThere are %hu chapters, do you want to start downloading with some chapter in particular? [y/N] ", foxchapters);
    scanf("%c", &yesno);
	scanf("%*[^\n]\n");
    if(yesno == 'y' || yesno == 'Y'){
        printf("Which chapter do you want to start for? ");
        scanf("%3hu", &i);
    }
    else
        i=1;
    if (i > foxchapters)
        printf("The chosed chapter does not exist, downloading from chapter 1\n");

    z = i;

    do{
        sprintf(p, "%.3hu", i);
        strcat(chapter, p);

        while (fgets(blkhtml, sizeof(blkhtml) -1, bf) != '\0'){
            if(strstr(blkhtml, chapter) && strstr(blkhtml, "1.html"))
                puts(strstr(blkhtml, path));
                found=1;
        }

        if(found==0){
            i++;
        }
        strcpy(chapter, "c");
        rewind(bf);
    }while(found==0);

    if (z != i)
        printf("Given chapter does not exist. Download will start from next available chapter (Chapter n. %hu)\n",i);

    for (i;i<=foxchapters;i++){
        sprintf(p, "%.3hu", i);
        strcat(chapter, p);

        while(fgets(blkhtml, sizeof(blkhtml) -1, bf) != '\0'){
            if(strstr(blkhtml, chapter) != '\0' && strstr(blkhtml, "1.html") != '\0'){
                mangafox(url_orig, name, downdir);
            }
        }
        strcpy(chapter, "c");
    }

return;
}
