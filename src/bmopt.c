#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void confdir_check(char[]);
void config(char confdir[]){
		FILE *cfg;
	char dfolder[70], configfile[70];
	short formatnum;

    strcpy(configfile, confdir);
    strcat(configfile, "baamanga.conf");
	chdir(confdir);
	cfg=fopen(configfile,  "w+");
	printf("When do you want your manga to be downloaded?: ");
	scanf(" %69s", dfolder);
	puts(dfolder);
	fprintf(cfg, "Downdir=%s\n", dfolder) ;

	printf("How do you want your downloaded manga?\n	1. image\n	2. pdf\n	3. cbz");
	printf ("\n ———————————————————————— \n") ;
	printf (" Introduce format number: ");
	scanf("%hu", &formatnum);
	if(formatnum==1)
		fprintf(cfg, "Format=image");
	else if (formatnum==2){
		fprintf(cfg, "Format=image");
		printf("You have chosen pdf, which is not yet supported, your manga Manga format set as image");
	}
	else if (formatnum==3){
		fprintf(cfg, "Format=image");
		printf("You have chosen cbz, which is not yet supported, your manga Manga format set as image");
	}
	fclose(cfg);
return;
}
