#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void domain_check(char[], char[]);
void confdir_check(char[]);
void downdir_check(char[]);

void config(char []);
void help();
void version();

void animea (char[], char[], char[]);
void danboru (char[], char[], char[]);
void ehentai (char[], char[], char[]);
void futahentai (char[], char[], char[]);
void mangafox (char[], char[], char[]);
void mangahere (char[], char[], char[]);
void mangareader (char[], char[], char[]);
void mangashare (char[], char[], char[]);
void pown (char[], char[], char[]);
void submanga (char[], char[], char[]);
void zerochan (char[], char[], char[]);


int main(int argc, char *argv[]) {
    //FILE *conf;
char url[100], downdir[60], confdir[30];

    /*strcpy(confdir, getenv("HOME"));
    strcat(confdir, "/.config/baamanga/");
    confdir_check(confdir);
    chdir(confdir);

    if( access( "baamanga.conf", F_OK ) == -1 ) {
        printf("\nConfiguration file does not exist. Please, wait a second and configure Baamanga.\n\n");
        config(confdir);
    }
    conf = fopen("baamanga.conf", "r");
    fgets(downdir, 59, conf);
    fclose(conf);

    strcpy(downdir, strrchr(downdir, '=')+1);
    downdir_check(downdir);*/

	strcpy(downdir, getenv("HOME"));
	strcat(downdir, "/Baamanga");
	downdir_check(downdir);

if (argc == 1){
printf("Welcome to Baamanga, the new manga downloader with lots of supported webpages.\nJust insert your download link and everything will be done automatically: ");

scanf("%99s", url);

domain_check(url, downdir);
}
    else if (argc == 2){
        if (strcmp(argv[1], "--config") == 0)
            config(confdir);

        else if (strcmp(argv[1], "--help") == 0)
            help();

        else if (strcmp(argv[1], "--version") == 0)
            version();

        else{
            strcpy(url, argv[1]);
            domain_check(url, downdir);
        }
}
    else if (argc > 2){
        short i;
        for (i=1;i <= argc; i++);{
            strcpy(url,argv[i]);
            domain_check(url, downdir);
        }
    }

return 0;
}

void domain_check(char url[], char downdir[]) {

char domain[20], url_orig[100], name[80];

    strcpy(url_orig, url) ;

    strtok(url, "/");
    strcpy(domain, strtok(NULL,"/"));

if (strcmp(domain, "manga.animea.net") == 0){						//ANIMEA
	printf("Manga from animea! I'd like to download it's anime aswell, soon maybe...\n");
	animea(url_orig, name, downdir);
	}
	else if (strcmp(domain, "danbooru.donmai.us") == 0){			//DANBORU
			printf("\nOk, you are downloading Danbooru boards, let's go\n");
			danboru(url_orig, name, downdir);
		}
	else if (strcmp(domain," e-hentai.org") == 0){					//E-HENTAI
			printf("\nWow, you are downloading manga from e-hentai, enjoy it!\n");
			ehentai(url_orig, name, downdir);
		}
	else if (strcmp(domain, "futahentai.com") == 0){				//FUTAHENTAI
			printf("\nMmm Futahentai, having fun huh? Let's download it!\n");
			futahentai(url_orig, name, downdir);
		}
	else if (strcmp(domain, "mangafox.me") == 0){					//MANGAFOX
			printf("\nMangafox! Good choice! Come on\n");
			mangafox(url_orig, name, downdir);
		}
	else if (strcmp(domain, "es.mangahere.co") == 0){				//MANGAHERE
			printf("\nThis is a Mangahere url isn't it? It's a very good manga site, starting download!\n");
			mangahere(url_orig, name, downdir);
			}
	else if (strcmp(domain, "www.mangareader.net") == 0){			//MANGAREADER
			printf("\nMmm mangareader, a classic! Good and varied, let's download it!\n");
			mangareader(url_orig, name, downdir);
		}
	else if (strcmp(domain, "read.mangashare.com") == 0){			//MANGASHARE
			printf("\nShared manga is better isn't it? Starting download\n");
			mangashare(url_orig, name, downdir);
		}
	else if (strcmp(domain, "www.pown.it") == 0){					//POWN
			printf("\nYeah good pown, let's share it\n");
			pown(url_orig, name, downdir);
		}
	else if (strcmp(domain, "submanga.com") == 0 ){					//SUBMANGA
			printf("\nThis is Submanga! The best Spanish manga site!\n");
			submanga(url_orig, name, downdir);
		}
	else if (strcmp(domain, "www.zerochan.net") == 0){			//ZEROCHAN
			printf("\nHey, good manga board, it is from Zerochan isn't it? Downloading!\n");
			zerochan(url_orig, name, downdir);
		}
	else
			printf("\nSorry, is not possible to download from this webpage, try with one bellow:\n-Submanga\n-Mcanime\n-Mangafox\n-Mangashare\n-Mangareader\n-Futahentai\n-E-hentai\n-4Chan\n-Zerochan\n-Danboru\n-Pown\n");

}
