#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <unistd.h>

void downdir_check(char []);
void namedir_check(char[], char[]);
void chapdir_check(char[], char[]);
void mangareadersingle(char[], char[], char[], char[], char[], short);
void mangareaderbulk(char[], char[], char[], char[], char[], char[], char[], short);
size_t write_data();


void mangareader(char url_orig[], char name[], char downdir[]){
    short j=0, len, slash = 0;
    char chapter[10], nameorig[80],code[7], chapname[13];

    //Name easy parsing
    while(url_orig[j] != '\0'){
        if (url_orig[j] == '/')
            slash++;
        j++;
    }
		//"long" kind of URL,  extract code
    if (slash == 5 || strstr(url_orig, ".html") != NULL)
        strcpy(code, strtok(NULL, "/"));

strcpy	(name, strtok (NULL, "/"));
strcpy	(nameorig, name);

	//formating name
	for (j=0;name[j]!='\0';j++){
        if(name[j] == '-')
        	name[j] = ' ';
        if (isalpha(name[j]) && name[j-1] == ' ')
        name[j] = toupper(name[j]);
    }
    if (isalpha(name[0]))
        	name[0] = toupper(name[0]);

	//Final formating and function choose
	len = strlen(name);

	if (name[len-5] == '.' || slash == 3){	//Bulk download
        if (slash == 4){	//remove ".html" of long, bulk URL
            strtok (name, ".");
            strtok (nameorig, ".");
        }
        //Start Bulk
	printf("\n  Name: %s\n", name);
	mangareaderbulk(url_orig, name, nameorig, chapname, chapter, code, downdir, slash);
	}
  //Single chapter, long URL download
	else if (slash == 5){
        strcpy(chapter,strtok (NULL,"."));
        strcpy(chapter, strrchr(chapter, '-') + 1);
        printf("\n	Name: %s\n	Chapter: %s", name, chapter);
        mangareadersingle(url_orig, name, nameorig, chapter, downdir, slash);
	}
    //Single chapter, short URL download
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
char tmpfile[34]="/tmp/.html-mangareader-";
char baseurl[]	="http://www.mangareader.net/";
	//to allow multiple instances of baamanga, one file by Manga
	strncat(tmpfile, name, 10);
    strtok(tmpfile, " ");

	//make directory
	namedir_check(name, downdir);
	strcat(strcat(downdir, "/"), name);
	chapdir_check(chapter, downdir);
	strcat(strcat(downdir, "/"), chapter);

    downdir_check(downdir);
	chdir(downdir);

    //urldown for long url system
    if(slash == 5){
        strcpy(urldown, url_orig);
        strtok(urldown, "/");
        strtok(NULL, "/");
        strcpy(urldown, strtok(NULL, "/"));
    }
    //urldown for short url system
    else if (slash == 4){
        strcpy(urldown, "/");
        strcat(urldown, nameorig);
        strcat(urldown, "/");
        strcat(urldown, chapter);
        strcat(urldown, "/");
    }

	while (err == 0){
		//restart "result" and "pgfound" values
		result		= 0;
		pgfound		= 0;
		//set "p" and "q" to enumerate "urldown" (next page to look for) and "imgname" (includes page number)
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
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, img);										//Where to save
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);							//Autoredirect


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

	remove(tmpfile);

return;
}

void mangareaderbulk(char url_orig[], char name[], char nameorig[], char chapname[], char chapter[], char code[], char downdir[], short slash){
    FILE *bf;
CURL *pcurl;
CURLcode pre;

unsigned short chapters=0, i=0, z=0;
char blkhtml[153600], p[4], yesno, path2[81], path[81], downdir_orig[60];
char blktmpfile[]="/tmp/.baamanga-bulk-mangareader";
bool found=0;
    //backup
    strcpy(downdir_orig, downdir);
    //Default path 1
    strcpy(path, nameorig);
    strcat(path, "/");
    strcat(path, "1\""); // adding \" to avoid i.e. "chapter-13" as first coincidence

    //Default path 2
    strcpy(path2, nameorig);
    strcat(path2, "/");
    strcat(path2, "chapter-1.html\""); // adding \" to avoid i.e. "chapter-13" as first coincidence

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
    //Count Chapters
    while (fgets(blkhtml, sizeof(blkhtml) -1, bf) != '\0'){
            //look for the path: style 1
            if (strstr(blkhtml, path) != '\0' && strstr(blkhtml, "chapter") == '\0'){
                while(path[strlen(path) -1] != '/')
                    path[strlen(path) -1] = '\0';
                while(path2[strlen(path2) -1] != '-')
                    path2[strlen(path2) -1] = '\0';

                chapters++;
            }

            //Look for path style: 2
            if (strstr(blkhtml, path2) != '\0' && strstr(blkhtml, code) != '\0'){
                while(path[strlen(path) -1] != '/')
                    path[strlen(path) -1] = '\0';
                while(path2[strlen(path2) -1] != '-')
                    path2[strlen(path2) -1] = '\0';

                chapters++;
            }
        }
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
    if (i > chapters)
        printf("The chosed chapter does not exist, downloading from chapter 1\n");

    z = i;
    //Check if given chapter exists. Program takes next chapter in case the given one doesn't exist
    while(found==0){
        sprintf(p, "%hu", i);

        while(path[strlen(path) -1] != '/')
            path[strlen(path) -1] = '\0';
        strcat(path,p);
        strcat(path,"\""); // adding \" to avoid i.e. "13" as first coincidence
        while(path2[strlen(path2) -1] != '-')
            path2[strlen(path2) -1] = '\0';
        strcat(path2, p);
        strcat(path2, ".html\""); // adding \" to avoid i.e. "chapter-13" as first coincidence
        while (fgets(blkhtml, sizeof(blkhtml) -1, bf) != '\0'){
            if (strstr(blkhtml, path) != '\0' && strstr(blkhtml, "chapter") == '\0'){
                found=1;
            }
            if (strstr(blkhtml, path2) != '\0' && strstr(blkhtml, code) != '\0'){
                found=1;
            }
        }
        if (found==0){
            rewind(bf);
            i++;
        }
    }
    rewind(bf);

    if (z != i)
        printf("Given chapter does not exist. Download will start from next available chapter (Chapter n. %s)\n", p);

    if(i > 1){
        //Look for chapter one (avoids find the chapter on "recents" list, which will cause problems)
        while(path[strlen(path) -1] != '/')
            path[strlen(path) -1] = '\0';
        strcat(path, "1\"");
        while(path2[strlen(path2) -1] != '-')
            path2[strlen(path2) -1] = '\0';
        strcat(path2, "1.html\"");

        found=0;
        while (fgets(blkhtml, sizeof(blkhtml) -1, bf) != '\0' && found == 0){
            if (strstr(blkhtml, path) != '\0' && strstr(blkhtml, "chapter") == '\0'){
                while(path[strlen(path) -1] != '/')
                    path[strlen(path) -1] = '\0';
                while(path2[strlen(path2) -1] != '-')
                    path2[strlen(path2) -1] = '\0';
                found=1;
            }
            if (strstr(blkhtml, path2) != '\0' && strstr(blkhtml, code) != '\0'){
                while(path[strlen(path) -1] != '/')
                    path[strlen(path) -1] = '\0';
                while(path2[strlen(path2) -1] != '-')
                    path2[strlen(path2) -1] = '\0';
                found=1;
            }
        }
    }

    //Download begins
    if(i > 1){
    strcat(path, p);
    strcat(path2, p);
    strcat(path2, ".html");
    }
    strcpy(url_orig, "http://www.mangareader.net/");
    slash++;

    while (fgets(blkhtml, sizeof(blkhtml) -1, bf) != '\0'){
        if (strstr(blkhtml, path) != '\0' && strstr(blkhtml, "chapter") == '\0'){
            strcat(url_orig, strtok(strstr(blkhtml, path), "\""));
            strcpy(chapter, strrchr(url_orig, '/'));
            memmove(chapter, chapter+1, strlen(chapter));
            printf("\n    Chapter: %s", chapter);
            mangareadersingle(url_orig, name, nameorig, chapter, downdir, slash);
            strcpy(url_orig, "http://www.mangareader.net/");
            while(path[strlen(path) -1] != '/')
                path[strlen(path) -1] = '\0';
            while(path2[strlen(path2) -1] != '-')
                path2[strlen(path2) -1] = '\0';
            strcpy(downdir, downdir_orig);
		}

        if (strstr(blkhtml, path2) != '\0' && strstr(blkhtml, code) != '\0'){
            strcat(url_orig, strtok(strstr(blkhtml, code), "\""));
            strcpy(chapter, strrchr(url_orig, '-'));
            memmove(chapter, chapter+1, strlen(chapter));
            strtok(chapter, ".");
            printf("\n    Chapter: %s", chapter);
            mangareadersingle(url_orig, name, nameorig, chapter, downdir, slash);
            strcpy(url_orig, "http://www.mangareader.net/");
            while(path[strlen(path) -1] != '/')
                path[strlen(path) -1] = '\0';
            while(path2[strlen(path2) -1] != '-')
                path2[strlen(path2) -1] = '\0';
            strcpy(downdir, downdir_orig);
        }
    }
	fclose(bf) ;
	remove(blktmpfile);
    printf("\n  Download Finished\n");

return;
}
