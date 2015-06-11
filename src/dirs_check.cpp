#include <iostream>
#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)
namespace fs = boost::filesystem;

bool ok=false;
struct stat d;
int check;
char yesno;
short int i;

void downdir_check(std::string downdir){
    do{
        if(!fs::exists(downdir)){
            fs::create_directory(downdir);
            ok = true;
        }
        else if (!fs::is_directory(downdir)){
		std::cout << _("A file with the download directory already exists.") << std::endl;
		std::cout << _("Do you want to overwrite with a directory? [y/N]") << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cin.get (yesno);

			if (yesno == 'y' || yesno == 'Y'){
				fs::remove (downdir);
				fs::create_directory(downdir);
				ok = true;
			}
			else{
				std::cout << _("Choose a new path to download your manga.") << std::endl;
				std::cout << _("(full path): ");
				getline (std::cin, downdir);
				ok = false;
				}
			}
        else ok = true;
	}while (ok == false);
}

void namedir_check(std::string name, std::string downdir){

	fs::current_path(downdir);
	ok=false;
	while (ok == false){

        if(!fs::exists(name))
            fs::create_directory(name);

        else if (!fs::is_directory(name)){
            std::cout << _("A file with the name of your manga already exists.") << std::endl;
            std::cout << _("Do you want to overwrite it? [y/N]") << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;
            std::cin.get(yesno);
            if (yesno == 'y'){
                fs::remove (name);
                fs::create_directory(name);
                ok = true;
            }
            else{
                std::cout << _("Choose a new directory to download ") << name << "." << std::endl;
                getline (std::cin, name);
            }
        }
        else ok = true;
	}
}

void chapdir_check(std::string chapter, std::string downdir){

	fs::current_path(downdir);
	ok=false;
	while (ok == false){
	if(!fs::exists(chapter))
        fs::create_directory(chapter);

	else if (!fs::is_directory(chapter)){
		std::cout << _("A file with the chapter of your manga already exists.\nDo you want to overwrite it? [y/N]") << std::endl;
		///std::cout << "(Use \"\" if space): ";
		std::cout << "-----------------------------------------------" << std::endl;
		std::cin.get (yesno);
			if (yesno== 'y'){
				fs::remove (chapter);
				fs::create_directory(chapter);
				ok = true;
			}
			else{
				std::cout << _("Choose a new directory to download the chapter.") << std::endl;
				///std::cout << "(Use \"\" if space): ";
				getline (std::cin, chapter);
				}
			}
    else ok = true;
	}
return;
}

void confdir_check(fs::path confdir){
fs::path confdirbackup=".config/baamanga.backup";

    if(!fs::exists(confdir))
        fs::create_directory(confdir);

	else if (!fs::is_directory(confdir)){
		std::cout << _("A file with the download directory name already exists.") << std::endl;
		std::cout << _("Saved as ") << confdir << _(".backup, making config directory.") << std::endl;
				fs::rename (confdir, confdirbackup);
				fs::remove (confdir);
				fs::create_directory(confdir);
			}
    else ok = true;
return;
}
