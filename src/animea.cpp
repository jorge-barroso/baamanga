#include <iostream>
#include <string>
#include "strings.h"
#include "download.h"
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)

void animeasingle(std::string, std::string, std::string, std::string, std::string);
void animeabulk(std::string, std::string, std::string, std::string);

void animea(std::string url, std::string name, std::string downdir){
std::string discr, chapter;
size_t found, limit;

    found = url.find_last_of("/") + 1;
    limit = url.find_last_of(".");
	discr = url.substr(found, limit - found);

	if((discr.find("chapter") != std::string::npos) == 1){
    //Name parsing
		name = discr.substr(0, discr.find("-chapter-"));
		//Now starts capitalizing
        /*for (unsigned short j=1; j<name.length(); j++){
            if (isalpha(name.at(j)) && name.at(j-1) == ' ')
                name.at(j) = toupper(name.at(j));
        }
        if (isalpha(name.at(0)))
            name.at(0) = toupper(name.at(0));
        */
        name = repair(name);
	//Chapter
        found = url.find_last_of("-") + 1;
        limit = url.find_last_of(".");
        ///discr = url.substr(found, limit - found -1);
        chapter = url.substr(found, limit - found);

        std::cout << "\t" << _("Name: ") << name << std::endl;
        std::cout << "\t" << _("Chapter: ") << chapter << std::endl;

		animeasingle(url, name, chapter, discr, downdir);
	}
	else{
	    name = discr.substr(0, discr.find(".html"));
	    //Now name repair
        name = repair(name);

		animeabulk(url, name, chapter, downdir);
	}

}

void animeasingle(std::string url, std::string name, std::string chapter, std::string discr, std::string downdir){

}

void animeabulk(std::string url, std::string name, std::string chapter, std::string downdir){

}
