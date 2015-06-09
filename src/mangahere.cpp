#include <iostream>
#include <string>
#include "strings.h"
#include "download.h"
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)

void mangaheresingle(std::string, std::string, std::string, std::string);
void mangaherebulk(std::string, std::string, std::string, std::string);

void mangahere(std::string url, std::string name, std::string downdir){
	std::string chapter;
    size_t found, limit;

    found = url.find("/", 9) + 1;
	found = url.find("/", found) + 1;
	limit = url.find("/", found);
	// Parse name
	name = url.substr(found, limit - found);

	name = repair(name);

    found = limit + 1;
    limit = url.find("/", found);
	chapter = url.substr(found, limit - found);

	if (chapter.compare("http:") == 0)
		mangaherebulk(url, name, chapter, downdir);
	else{
		chapter = url.substr(limit +1);
        chapter.back() = '\0';
		mangaheresingle(url, name, chapter, downdir);
	}
		std::cout << "\t" << _("Name: ") << name << std::endl;
		std::cout << "\t" << _("Chapter: ") << chapter << std::endl;
return;
}


void mangaheresingle(std::string url, std::string name, std::string chapter, std::string downdir){
std::cout << _("This is mangaheresingle (under development)");
return;
}

void mangaherebulk(std::string url, std::string name, std::string chapter, std::string downdir){
std::cout << _("This is mangaherebulk (under development)");
return;
}
