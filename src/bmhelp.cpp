#include <iostream>
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)

void help(){

std::cout << _("USAGE: baamanga [arguments] [url]") << std::endl;
std::cout << _("Both [arguments] and [url] are optional") << std::endl;
std::cout << _("Options are:") << std::endl;
std::cout << "\t" << _("config") << "\t\t\t\t" << _("Show config dialog") << std::endl;
std::cout << "\t" <<   "\n";
std::cout << "\t" << _("version") << "\t\t\t\t" << _("Print version information and exit") << std::endl;
std::cout << "\t" <<   "\n";
std::cout << "\t" << _("help") << "\t\t\t\t" << _("Show this dialog") << std::endl;
}
