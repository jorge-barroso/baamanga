#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>
#include "bmopt.c"
#include "bmhelp.c"
#include "bmver.c"
#include "animea.c"
#include "danboru.c"
#include "mangafox.c"
#include "mangahere.c"
#include "mangareader.c"
#include "mangashare.c"
#include "pown.c"
#include "submanga.c"
#include "zerochan.c"

void config();
void help();
void version();
void animea (char[], char[], char[]);
void danboru (char[], char[], char[]);
void mangafox (char[], char[], char[]);
void mangahere (char[], char[], char[]);
void mangareader (char[], char[], char[]);
void mangashare (char[], char[], char[]);
void pown (char[], char[]);
void submanga (char[], char[], char[]);
void zerochan (char[], char[], char[]);


char downdir[60]="/home/jorge/Descargas/Recibo";
bool ok;

void downdir_check(){
	struct stat d;
	int check/*, length = strlen(downdir)*/;
	char ow;
	
		
	while (ok == 0){
	check = lstat(downdir, &d);
	if (check == -1){
		if(ENOENT == errno){
			mkdir (downdir, (S_IWUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
			ok = 1;
		}
		else {
        perror("stat");
        exit(1);
    }
} 
	else if (!S_ISDIR(d.st_mode));{
		printf ("A file with the download directory already exists, do you want to overwrite with a directory? [y/N]\n");
		printf ("---------------------------------------------------------------------------------------------------\n");
		scanf ("%c", &ow);
			
			if (ow == 'y'){
				remove (downdir);
				mkdir (downdir, (S_IWUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
				ok = 1;
			}
			else{
				printf("Choose a new path to download your manga: ");
				scanf(" %s", downdir);
			}
		}
	}
}


int main(int argc, char *argv[2]) {

char url[100], protocol[5], domain[20], url_orig[100], name[50], chapter[4];

		downdir_check();

if (argc == 2){
	if (strcmp(argv[1], "--config") == 0)
		config();
	
	else if (strcmp(argv[1], "--help") == 0)
		help();
	
	else if (strcmp(argv[1], "--version") == 0)
		version();
		
	else
		strcpy(url, argv[1]);
}

else{
printf("Insert download link: ");

scanf("%99s", url);
}
if (url != '\0'){
strcpy(url_orig, url) ;

strcpy (protocol, strtok(url, ":"));

	strcpy(domain, strtok(NULL,"/"));
if (strcmp(domain, "manga.animea.net") == 0)					//ANIMEA
	animea(url_orig, name, chapter);
	else if (strcmp(domain, "danbooru.donmai.us") == 0)			//DANBORU
			danboru(url_orig, name, chapter);
	else if (strcmp(domain, "mangafox.me") == 0)				//MANGAFOX
			mangafox(url_orig, name, chapter);
	else if (strcmp(domain, "es.mangahere.co") == 0)			//MANGAHERE
			mangahere(url_orig, name, chapter);
	else if (strcmp(domain, "read.mangareader.net") == 0)		//MANGAREADER
			mangareader(url_orig, name, chapter);
	else if (strcmp(domain, "read.mangashare.com") == 0)		//MANGASHARE
			mangashare(url_orig, name, chapter);
	else if (strcmp(domain, "www.pown.it") == 0)				//POWN
			pown(url_orig, name);
	else if (strcmp(domain, "submanga.com") == 0 )				//SUBMANGA
			submanga(url_orig, name, chapter);
	else if (strcmp(domain, "www.zerochan.net") == 0)			//ZEROCHAN
			zerochan(url_orig, name, chapter);
	else
			printf("Sorry, is not possible to download from this webpage, try with one bellow:\n-Submanga\n-Mcanime\n-Mangafox\n-Mangashare\n-Mangareader\n-Futahentai\n-E-hentai\n-4Chan\n-Zerochan\n-Danboru\n-Pown");
			
}
return 0;
}
