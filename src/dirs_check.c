#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

bool ok=0;
struct stat d;
int check;
char yesno;
short int i;

void downdir_check(char downdir[]){

    while (ok == 0){
        check = lstat(downdir, &d);
        if (check == -1){
            if(ENOENT == errno){
                for (i=0;i<2;i++){
                    if (downdir[i] == '~' && downdir[i+1] == '/'){
                    downdir[i] = '\0';
                    downdir[i+1] = '\0';
                    chdir(getenv("HOME"));
                    }
                }
                mkdir (downdir, 0755);
                ok = 1;
            }
		else {
            perror("stat");
            exit(1);
            ok=1;
        }
        }
	else if (S_ISDIR(d.st_mode)){
		ok = 1;
		}
		else{
		printf ("A file with the download directory already exists.\nDo you want to overwrite with a directory? [y/N]\n");
		printf ("-----------------------------------------------\n");
		scanf ("%1c", &yesno);
		scanf("%*[^\n]\n");
			if (yesno== 'y'){
				remove (downdir);
				for (i=0;i<2;i++);{
				if (downdir[i] == '~' && downdir[i+1] == '/'){
				downdir[i] = '\0';
				downdir[i+1] = '\0';
				chdir(getenv("HOME"));
				printf("%s\n", downdir);
			}
			}
				mkdir (downdir, 0755);
				ok = 1;
			}
			else{
				printf("Choose a new PATH to download your manga\n(full path with "" if space): ");
				scanf("%s", downdir);
				}
			}

	}
return;
}

void namedir_check(char name[], char downdir[]){

	chdir(downdir);
	ok=0;
	while (ok == 0){
	check = lstat(name, &d);
	if (check == -1){
		if(ENOENT == errno){
			mkdir (name, 0755);
			ok = 1;
		}
		else {
        perror("stat");
        exit(1);
        ok=1;
		}
	}
	else if (S_ISDIR(d.st_mode)){
		ok = 1;
		}
		else{
		printf ("A file with the name of your manga already exists.\nDo you want to overwrite it? [y/N]\n");
		printf ("-----------------------------------------------\n");
		scanf ("%1c", &yesno);
		scanf("%*[^\n]\n");
			if (yesno== 'y'){
				remove (name);
				mkdir (name, 0755);
				ok = 1;
			}
			else{
				printf("Choose a new directory to download %s\n(Use "" if space): ", name);
				scanf("%s", name);
				}
			}

	}
return;
}

void chapdir_check(char chapter[], char downdir[]){

	chdir(downdir);
	ok=0;
	while (ok == 0){
	check = lstat(chapter, &d);
	if (check == -1){
		if(ENOENT == errno){
			mkdir (chapter, 0755);
			ok = 1;
		}
		else {
        perror("stat");
        exit(1);
        ok=1;
		}
	}
	else if (S_ISDIR(d.st_mode)){
		ok = 1;
		}
		else{
		printf ("A file with the chapter of your manga already exists.\nDo you want to overwrite it? [y/N]\n");
		printf ("-----------------------------------------------\n");
		scanf ("%1c", &yesno);
		scanf("%*[^\n]\n");
			if (yesno== 'y'){
				remove (chapter);
				mkdir (chapter, 0755);
				ok = 1;
			}
			else{
				printf("Choose a new directory to download the chapter\n(Use "" if space): ");
				scanf("%s", chapter);
				}
			}

	}
return;
}

void confdir_check(char confdir[]){
char confdirbackup[]=".config/baamanga.backup";

    chdir(getenv("HOME"));

	check = lstat(confdir, &d);
	if (check == -1){
		if(ENOENT == errno){
			mkdir (confdir, 0755);
		}
		else {
        perror("stat");
        exit(1);
		}
	}
	else if (S_ISDIR(d.st_mode)){
		ok = 1;
		}
		else{
		printf ("A file with the download directory already exists.\nSaved as %s.backup, making config directory\n", confdir);
				rename (confdir, confdirbackup);
				remove (confdir);
				mkdir (confdir, 0755);
			}
return;
}
