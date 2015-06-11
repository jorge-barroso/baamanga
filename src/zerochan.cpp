#include <iostream>
#include <string>
#include "strings.h"
#include "download.h"
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)

void zerochansingle(std::string, std::string, std::string);
void zerochanbulk(std::string, std::string, std::string);

void zerochan(std::string url, std::string name, std::string downdir){
short unsigned int j;
bool discr;

	name = url.substr(url.find("/", 9) + 1);

	for(j=0;name.at(j)!='\0';j++){
		if (name.at(j) == '+' || isalpha(name.at(j)))
		discr = true;
	}
	if (discr == true){
		name = repair(name);
		zerochanbulk(url, name, downdir);
	}
	else
		std::cout << _("Please, give a name for the file you are going to download");
		getline(std::cin, name);
		 zerochansingle(url, name, downdir);
}

void zerochansingle(std::string url, std::string name, std::string downdir){
std::cout << _("This is zerochansingle (under development)");
return;
}

void zerochanbulk(std::string url, std::string name, std::string downdir){

std::cout << _("This is zerochanbulk(under development)");
return;
}
