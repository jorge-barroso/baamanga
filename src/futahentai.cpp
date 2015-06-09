#include <iostream>
#include <string>
#include "strings.h"
#include "download.h"
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)

void futahentai(std::string url, std::string name, std::string downdir){
short found, limit;
std::string chapter;

    //Let's parse the name
	found = url.find("-") + 1;
	limit = url.find("-", found);
	name = url.substr(found, limit - found - 1);
	name = repair(name);
	//Parsing chapter
	found = limit + 1;
	limit = url.find(".", found);
	chapter = url.substr(found, limit - found - 1);

    std::cout << "\n";
	std::cout << "\t" << _("Name: ") << name << std::endl;
	std::cout << "\t" << _("Chapter: ") << chapter << std::endl;

return;
}
