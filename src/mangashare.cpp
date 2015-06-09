#include <iostream>
#include <string>
#include "strings.h"
#include "download.h"

#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)

void mangashare(std::string url, std::string name, std::string downdir){
std::string chapter;
size_t found, limit;

	//Name parse
	found = url.find("/", 9) + 1;
	limit = url.find("/", found);
	name = url.substr(found, limit - found);

    name = repair(name);
    //Parse chapter
    found = url.find("-", limit) + 1;
    limit = url.find ("/", found);
    chapter = url.substr(found, limit - found);

std::cout << "\n\t" << _("Name: ") << name << std::endl;
std::cout << "\t" << _("Chapter: ")<< chapter << std::endl;
}
