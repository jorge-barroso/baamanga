#include <iostream>
#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

bool ok=0;
struct stat d;
int check;
char yesno;
short int i;

void downdir_check(string downdir){
    for (i=0;i<2;i++){
        if (downdir.at(i) == '~' && downdir.at(i+1) == '/'){
        downdir.erase(0,2);
        chdir(getenv("HOME"));
        }
    }
    do{
        check = stat(downdir.c_str(), &d);
        if (check == -1){
            if(ENOENT == errno){
                mkdir (downdir.c_str(), 0755);
                ok = 1;
            }
		else {
            exit(1);
            ok=1;
        }
        }
	else if (S_ISDIR(d.st_mode)){
		ok = 1;
		}
		else{
		cout << "A file with the download directory already exists." << endl;
		cout << "Do you want to overwrite with a directory? [y/N]" << endl;
		cout << "-----------------------------------------------" << endl;
		cin.get (yesno);

			if (yesno == 'y' || yesno == 'Y'){
				remove (downdir.c_str());
				for (i=0;i<2;i++);{
                    if (downdir.at(i) == '~' && downdir.at(i+1) == '/'){
                    downdir.at(i) = '\0';
                    downdir.at(i+1) = '\0';
                    chdir(getenv("HOME"));
                    }
                }
				mkdir (downdir.c_str(), 0755);
				ok = 1;
			}
			else{
				cout << "Choose a new PATH to download your manga." << endl;
				cout << "(full path with \"\" if space): ";
				getline (cin, downdir);
				ok=0;
				}
			}
	}while (ok == 0);
return;
}

void namedir_check(string name, string downdir){

	chdir(downdir.c_str());
	ok=0;
	while (ok == 0){
	check = stat(name.c_str(), &d);
	if (check == -1){
		if(ENOENT == errno){
			mkdir (name.c_str(), 0755);
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
		cout << "A file with the name of your manga already exists." << endl;
		cout << "Do you want to overwrite it? [y/N]" << endl;
		cout << "-----------------------------------------------" << endl;
		cin.get(yesno);
			if (yesno== 'y'){
				remove (name.c_str());
				mkdir (name.c_str(), 0755);
				ok = 1;
			}
			else{
				cout << "Choose a new directory to download " << name << "." << endl;
				cout << "(Use \"\" if space): ";
				getline (cin, name);
				}
			}

	}
return;
}

void chapdir_check(string chapter, string downdir){

	chdir(downdir.c_str());
	ok=0;
	while (ok == 0){
	check = lstat(chapter.c_str(), &d);
	if (check == -1){
		if(ENOENT == errno){
			mkdir (chapter.c_str(), 0755);
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
		cout << "A file with the chapter of your manga already exists.\nDo you want to overwrite it? [y/N]" << endl;
		cout << "-----------------------------------------------" << endl;
		cin.get (yesno);
			if (yesno== 'y'){
				remove (chapter.c_str());
				mkdir (chapter.c_str(), 0755);
				ok = 1;
			}
			else{
				cout << "Choose a new directory to download the chapter." << endl;
				cout << "(Use \"\" if space): ";
				getline (cin, chapter);
				}
			}

	}
return;
}

void confdir_check(string confdir){
string confdirbackup=".config/baamanga.backup";

    chdir(getenv("HOME"));

	check = lstat(confdir.c_str(), &d);
	if (check == -1){
		if(ENOENT == errno){
			mkdir (confdir.c_str(), 0755);
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
		cout << "A file with the download directory name already exists." << endl;
		cout << "Saved as " << confdir << ".backup, making config directory." << endl;
				rename (confdir.c_str(), confdirbackup.c_str());
				remove (confdir.c_str());
				mkdir (confdir.c_str(), 0755);
			}
return;
}
