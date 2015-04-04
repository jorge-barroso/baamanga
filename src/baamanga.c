#include <stdio.h>
#include <string.h>
#include "bmopt.c"
#include "bmhelp.c"
#include "bmver.c"
#include "animea.c"
#include "danboru.c"
#include "ehentai.c"
#include "futahentai.c"
#include "mangafox.c"
#include "mangareader.c"
#include "mangashare.c"
//#include "mcanime.c" due to copyright issues is not possible to read Manga on mcanime 
#include "pown.c"
#include "submanga.c"
#include "zerochan.c"

void config();
void help();
void version();
void submanga (char[], char[], char[]);
void mcanime (char[], char[], char[]);
void mangafox (char[], char[], char[]);
void mangashare (char[], char[], char[]);
void mangareader (char[], char[], char[]);
void animea (char[], char[], char[]);
void futahentai (char[], char[], char[]);
void ehentai (char[], char[], char[]);
void zerochan (char[], char[], char[]);
void danboru (char[], char[], char[]);
void pown (char[], char[], char[]);
// void checking (char[],char); //Future URL checking function

char name[50];

int main(int argc, char *argv[2]) {

short int err;
char url[100], protocol[5], domain[20], url_orig[100];
//char check; //Future URL checking function
//char url_check[100]; //Future URL checking function

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
// strcpy(url_check, url); //Future URL checking function
strcpy(url_orig, url) ;

strcpy (protocol, strtok(url, ":"));

	strcpy(domain, strtok(NULL,"/"));
if (strcmp(domain, "submanga.com") == 0 )
	submanga(url_orig, protocol, name);
	/*else if (strcmp(domain, "www.mcanime.net") == 0)
			mcanime(url_orig, protocol, name);*/
	else if (strcmp(domain, "mangafox.me") == 0)
			mangafox(url_orig, protocol, name);
	else if (strcmp(domain, "www.mangashare.com") == 0)
			mangashare(url_orig, protocol, name);
	else if (strcmp(domain, "read.mangareader.net") == 0)
			mangareader(url_orig, protocol, name);
	else if (strcmp(domain, "manga.animea.net") == 0)
			animea(url_orig, protocol, name);
	else if (strcmp(domain, "futahentai.com") == 0)
			futahentai(url_orig, protocol, name);
	else if (strcmp(domain," e-hentai.org") == 0)
			ehentai(url_orig, protocol, name);
	else if (strcmp(domain, "www.zerochan.com") == 0)
			zerochan(url_orig, protocol, name);
	else if (strcmp(domain, "danbooru.donmai.us") == 0)
			danboru(url_orig, protocol, name);
	else if (strcmp(domain, "www.pown.it") == 0)
			pown(url_orig, protocol, name);
	else{
			printf("Sorry, is not possible to download from this webpage, try with one bellow:\n-Submanga\n-Mcanime\n-Mangafox\n-Mangashare\n-Mangareader\n-Futahentai\n-E-hentai\n-4Chan\n-Zerochan\n-Danboru\n-Pown");
			err = 1;		
		}
		if (err != 1)
			printf ("Download finished, you can see %s into your download folder\n", name);
}
return 0;
}
