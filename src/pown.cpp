#include <iostream>
#include <string>
#include <curl/curl.h>
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)

void pown(std::string url, std::string name, std::string downdir){
std::cout << _("This is Pown (under development)") << std::endl;
//std::cout << _("Give a name to the pown: ");
//std::getline(std::cin, name);
}
