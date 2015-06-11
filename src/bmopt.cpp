#include <iostream>
#include <string>
#include <fstream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)
namespace fs = boost::filesystem;

void confdir_check(fs::path);

void config(fs::path confdir){
    std::ofstream conf;
	std::string dfolder;
	short formatnum;

	fs::current_path(confdir);

	std::cout << _("Where do you want your manga to be downloaded?: ");
	getline(std::cin, dfolder);
    if (dfolder.at(0) == '~' && dfolder.at(1) == '/'){
            dfolder.erase(0 , 2);
    }

	std::cout << _("How do you want your downloaded manga?") << std::endl;
	std::cout << "\t" << _("1. image") << std::endl << "\t" << _("2. pdf") << std::endl << "\t" << _("3. cbz") << "\n" << std::endl;
	std::cout << "\t" << _("Introduce format number: ");
	std::cin >> formatnum;

    while (formatnum != 1 && formatnum != 2 && formatnum != 3){
	std::cout << "Format number is incorrect, try again:" << std::endl;
	std::cout << "\t" << _("1. image") << std::endl << "\t" << _("2. pdf") << std::endl << "\t" << _("3. cbz") << "\n" << std::endl;
	std::cout << "\t" << _("Introduce format number: ");
	std::cin >> formatnum;
	}

    conf.open("baamanga.conf");
    conf << "Downdir=" + dfolder + "\n";
	if(formatnum==1)
		conf << "Format=image";
	else if (formatnum==2){
		conf << "Format=image";
		std::cout << _("You have chosen pdf, which is not yet supported, manga format set as image.") << std::endl;
	}
	else if (formatnum==3){
		conf << "Format=image";
		std::cout << _("You have chosen cbz, which is not yet supported, manga format set as image.") << std::endl;
	}
	conf.close();
return;
}
