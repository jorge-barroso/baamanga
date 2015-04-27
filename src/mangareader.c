#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <unistd.h>

void namedir_check(char[], char[]);
void chapdir_check(char[], char[]);
void mangareadersingle(char[], char[], char[], char[], char[], short);
void mangareaderbulk(char[], char[], char[], char[], char[], char[], char[], short);
size_t write_data();


void mangareader(char url_orig[], char name[], char downdir[]){
    short j=0, len, slash = 0;
    char chapter[4], nameorig[80],code[7], chapname[13];

    //Name easy parsing
    while(url_orig[j] != '\0'){
        if (url_orig[j] == '/')
            slash++;
        j++;
    }

    if (slash == 5 || strstr(url_orig, ".html") != NULL)
        strcpy(code, strtok(NULL, "/"));

strcpy	(name, strtok (NULL, "/"));
strcpy	(nameorig, name);

	for (j=0;name[j]!='\0';j++){
        if(name[j] == '-')
        	name[j] = ' ';
        if (isalpha(name[j]) && name[j-1] == ' ')
        name[j] = toupper(name[j]);
    }
    if (isalpha(name[0]))
        	name[0] = toupper(name[0]);

	len = strlen(name);

	if (name[len-5] == '.' || slash == 3){
        if (slash == 4){
            strtok (name, ".");
            strtok (nameorig, ".");
        }
	printf("\n  Name: %s\n", name);
	mangareaderbulk(url_orig, name, nameorig, chapname, chapter, code, downdir, slash);
	}
	else if (slash == 5){
        strcpy(chapter,strtok (NULL,"."));
        strcpy(chapter, strrchr(chapter, '-') + 1);
        printf("\n	Name: %s\n	Chapter: %s", name, chapter);
        mangareadersingle(url_orig, name, nameorig, chapter, downdir, slash);
	}
    else if (slash == 4){
        strcpy(chapter, strrchr (url_orig,'/') + 1);
        printf("\n	Name: %s\n	Chapter: %s", name, chapter);
        mangareadersingle(url_orig, name, nameorig, chapter, downdir,slash);
    }
}

void mangareadersingle(char url_orig[], char name[], char nameorig[], char chapter[], char downdir[], short slash){

	FILE *fp;
	FILE *img;
CURL *curl;
CURLcode res;
bool err = 0, result, pgfound;
short i=1;
char urldown[100],imgname[8], q[4], p[4], html[153600], pageurl[100];
char tmpfile[33]="/tmp/.html-mangareader";
char baseurl[]	="http://www.mangareader.net/";

	strncat(tmpfile, name, 10);
    strtok(tmpfile, " ");

	namedir_check(name, downdir);
	strcat(strcat(downdir, "/"), name);
	chapdir_check(chapter, downdir);
	strcat(strcat(downdir, "/"), chapter);
	chdir(downdir);

    if(slash == 5){
        strcpy(urldown, url_orig);
        strtok(urldown, "/");
        strtok(NULL, "/");
        strcpy(urldown, strtok(NULL, "/"));
    }
    else if (slash == 4){
        strcpy(urldown, "/");
        strcat(urldown, strcat(nameorig, "/"));
        strcat(urldown, chapter);
        strcat(urldown, "/");
    }

	while (err == 0){
		result		= 0;
		pgfound		= 0;
		sprintf		(p, "%d", i+1);
		sprintf		(q, "%.3d", i);
		strcpy		(imgname, q);
		strcat		(imgname, ".jpg");

        if (slash == 5){
            while (urldown[strlen(urldown) -1] != '-'){
                urldown[strlen(urldown) -1] = '\0';
            }
		}
		else if (slash == 4){
            while (urldown[strlen(urldown) -1] != '/'){
                urldown[strlen(urldown) -1] = '\0';
            }
		}
		strcat		(urldown, p);

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

	fp = fopen (tmpfile, "r");


    while (fgets(html, sizeof(html) - 1, fp) != '\0' && result != 1){
		if (strstr(html, urldown) != NULL){

            if (slash == 5){
                strcpy (url_orig, baseurl);
                strcat (url_orig, strtok(strstr(html, urldown),"\'"));
            }

            else if (slash == 4){
                if (i > 1){
                    while(url_orig[strlen(url_orig) -1] != '/')
                    url_orig[strlen(url_orig) -1] = '\0';
                }
                else
                    strcat(url_orig, "/");

                strcat(url_orig, p);
            }

            result = 1;
		}
	}

	rewind(fp);

	if (result == 0)
		err = 1;

	while (fgets(html, sizeof(html) - 1, fp) != '\0'){
		if (strstr(html, "http:") != NULL && strstr(html, nameorig) != NULL && strstr(html, ".jpg") != NULL){
			strcpy (pageurl, strtok(strstr(html, "http:"), "\""));
			pgfound	= 1;
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
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);					//Autoredirect


		res = curl_easy_perform(curl);
		fclose(img);

		if(res != CURLE_OK){
			err = 1;
				}

		curl_easy_cleanup(curl);
			}
		}

	i++;
	}

	if (i > 2)
		printf("\n\n%s chapter %s downloaded\n", name, chapter);

return;
}

void mangareaderbulk(char url_orig[], char name[], char nameorig[], char chapname[], char chapter[], char code[], char downdir[], short slash){
    FILE *bf;
    FILE *tmpchap;

CURL *pcurl;
CURLcode pre;

unsigned short chapters=0, i=0/*, k=1, z=*/;
char blkhtml[153600]/*, p[4]*/, q[4], yesno, path2[81], path[81], next[4]/*, blkurldown[40]*/;
char blktmpfile[]="/tmp/.baamanga-bulk-mangareader";
char chaplist[] = "/tmp/.mangareader-chaplist";
//bool err=0;
    //Default path 1
    strcpy(path, nameorig);
    strcat(path, "/");
    strcat(path, "1");

    //Default path 2
    strcpy(path2, nameorig);
    strcat(path2, "/");
    strcat(path2, "chapter-1");

    //Download html
    pcurl = curl_easy_init();
    if(pcurl) {
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
	}

    bf      =   fopen(blktmpfile, "r");
    tmpchap =   fopen(chaplist, "w+");

    //while(err != 1){
        while (fgets(blkhtml, sizeof(blkhtml) -1, bf) != '\0'){
            //look for the path style 1
            if (strstr(blkhtml, path) != '\0'){
                fprintf(tmpchap, "%s\n", strstr(blkhtml, path));
                chapters++;
                sprintf(next, "%hu", chapters+1);

                while(path[strlen(path) -1] != '/'){
                        path[strlen(path) -1] = '\0';
                }
                strcat(path, next);
                while(path2[strlen(path2) -1] != '-'){
                        path2[strlen(path2) -1] = '\0';
                }
                strcat(path2, next);
                strcat(path2, ".html");
                //err = 0;
            }
            /*else
                err = 1;*/
            //Look for path style 2
            if (strstr(blkhtml, path2) != '\0' && strstr(blkhtml, code) != '\0'){
                fprintf(tmpchap, "%s\n", strstr(blkhtml, code));
                chapters++;
                //puts(strstr(blkhtml, code));
                sprintf(next, "%hu", chapters+1);
                //modify next path and path2 to look for.
                while(path[strlen(path) -1] != '/'){
                        path[strlen(path) -1] = '\0';
                }
                strcat(path, next);
                while(path2[strlen(path2) -1] != '-'){
                        path2[strlen(path2) -1] = '\0';
                }
                strcat(path2, next);
                strcat(path2, ".html");

                //err = 0;
            }
            /*else
                err = 1;*/
        }
    //}
    rewind(bf);

    //Ask for the first chapter to download for. Take 1 if not specified
    printf("\nThere are %hu chapters, do you want to start downloading with some chapter in particular? [y/N] ", chapters);
		scanf("%c", &yesno);
		scanf("%*[^\n]\n");
    if(yesno == 'y' || yesno == 'Y'){
        printf("Which chapter do you want to start for? ");
        scanf("%3hu", &i);
		scanf("%*[^\n]\n");
    }
    else
        i=1;
    //Start downloading chapters
    for(;i<=chapters;i++){
           sprintf(q, "%hu", i);
           strcpy(url_orig, "http://www.mangareader.net/");
           /*while (fgets(blkhtml, sizeof(blkhtml) -1, bf) != '\0'){
           if (){
       }*/
           }

return;
}
