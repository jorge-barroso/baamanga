#include <stdio.h>
#include <string.h>
#include "checking.c"
#include "protocols.c"


void submanga (char[]);
void mcanime (char[]);
void mangafox (char[]);
void mangashare (char[]);
void mangareader (char[]);
void animea (char[]);
void futahentai (char[]);
void ehentai (char[]);
void fchan (char[]);
void zerochan (char[]);
void danboru (char[]);
void pown (char[]);
char checking (char);

char url_orig[100];
char check;

int main() {

char url[100], url_check[100], domain[20];


printf("Insert download link: ");

scanf("%99s", url);

strcpy(url_check, url);
strcpy(url_orig, url) ;

checking(url_check);

if (check == 'y'){
	
	strtok(url, "/") ;

	strcpy(domain, strtok(NULL,"/"));
	if (strcmp(domain, "submanga.com") == 0 )
		submanga(url_orig);
		else if (strcmp(domain, "www.mcanime.net") == 0)
				mcanime(url_orig);
		else if (strcmp(domain, "mangafox.me") == 0)
				mangafox(url_orig);
		else if (strcmp(domain, "mangashare.com") == 0)
				mangashare(url_orig);
		else if (strcmp(domain, "mangareader.net") == 0)
				mangareader(url_orig);
		else if (strcmp(domain, "manga.animea.com") == 0)
				animea(url_orig);
		else if (strcmp(domain, "futahentai.com") == 0)
				futahentai(url_orig);
		else if (strcmp(domain, e-hentai.org") == 0)
				ehentai(url_orig);
		else if (strcmp(domain, "www.zerochan.com") == 0)
				zerochan(url_orig);
		else if (strcmp(domain, "danbooru.donmai.us") == 0)
				danboru(url_orig);
		else if (strcmp(domain, "www.pown.it") == 0)
				pown(url_orig);
		else
				printf("Sorry, is not possible to download from this webpage, try with one bellow:\n-Submanga\n-Mcanime\n-Mangafox\n-Mangashare\n-Mangareader\n-Futahentai\n-E-hentai\n-4Chan\n-Zerochan\n-Danboru\n-Pown");
		
		printf ("Download finished, you can see your manga into your download folder");
}

else
	printf("Unable to parse URL, please try a valid URL. Try one of this:\n-Submanga\n-Mcanime\n-Mangafox\n-Mangashare\n-Mangareader\n-Futahentai\n-E-hentai\n-4Chan\n-Zerochan\n-Danboru\n-Pown");
	
return 0;

} 
