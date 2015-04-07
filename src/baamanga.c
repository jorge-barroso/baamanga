#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmopt.c"
#include "bmhelp.c"
#include "bmver.c"
#include "downdir_check.c"
#include "animea.c"
#include "danboru.c"
#include "ehentai.c"
#include "futahentai.c"
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
void downdir_check(char[]);
void animea (char[], char[], char[], char[]);
void danboru (char[], char[], char[], char[]);
void ehentai (char[], char[], char[], char[]);
void futahentai (char[], char[], char[], char[]);
void mangafox (char[], char[], char[], char[]);
void mangahere (char[], char[], char[], char[]);
void mangareader (char[], char[], char[], char[]);
void mangashare (char[], char[], char[], char[]);
void pown (char[], char[], char[]);
void submanga (char[], char[], char[], char[]);
void zerochan (char[], char[], char[], char[]);


int main(int argc, char *argv[2]) {

char url[100], protocol[5], domain[20], url_orig[100], name[50], chapter[4], downdir[60]="/home/jorge/Descargas/Recibo 1";
		
		downdir_check(downdir);

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
	animea(url_orig, name, chapter, downdir);
	else if (strcmp(domain, "danbooru.donmai.us") == 0)			//DANBORU
			danboru(url_orig, name, chapter, downdir);
	else if (strcmp(domain," e-hentai.org") == 0)				//E-HENTAI
			ehentai(url_orig, name, chapter, downdir);
	else if (strcmp(domain, "futahentai.com") == 0)				//FUTAHENTAI
			futahentai(url_orig, name, chapter, downdir);
	else if (strcmp(domain, "mangafox.me") == 0)				//MANGAFOX
			mangafox(url_orig, name, chapter, downdir);
	else if (strcmp(domain, "es.mangahere.co") == 0)			//MANGAHERE
			mangahere(url_orig, name, chapter, downdir);
	else if (strcmp(domain, "read.mangareader.net") == 0)		//MANGAREADER
			mangareader(url_orig, name, chapter, downdir);
	else if (strcmp(domain, "read.mangashare.com") == 0)		//MANGASHARE
			mangashare(url_orig, name, chapter, downdir);
	else if (strcmp(domain, "www.pown.it") == 0)				//POWN
			pown(url_orig, name, downdir);
	else if (strcmp(domain, "img.submanga.com") == 0 )				//SUBMANGA
			submanga(url_orig, name, chapter, downdir);
	else if (strcmp(domain, "www.zerochan.net") == 0)			//ZEROCHAN
			zerochan(url_orig, name, chapter, downdir);
	else
			printf("Sorry, is not possible to download from this webpage, try with one bellow:\n-Submanga\n-Mcanime\n-Mangafox\n-Mangashare\n-Mangareader\n-Futahentai\n-E-hentai\n-4Chan\n-Zerochan\n-Danboru\n-Pown");
			
}
return 0;
}
