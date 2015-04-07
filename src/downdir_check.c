#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
bool ok;

void downdir_check(char downdir[]){
	struct stat d;
	int check/*, length = strlen(downdir)*/;
	char ow;
	short int i;
	
while (ok == 0){
	check = lstat(downdir, &d);
	if (check == -1){
		if(ENOENT == errno){
			for (i=0;i<2;i++);{
				if (downdir[i] == '~' && downdir[i+1] == '/'){
				downdir[i] = '\0';
				downdir[i+1] = '\0';
				printf("%s\n", downdir);
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
		scanf ("%1c", &ow);
		scanf("%*[^\n]\n");
			if (ow == 'y'){
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
}
