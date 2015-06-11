#include <iostream>
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)

void version(){
std::cout << _("Baamanga version 0.5.6 (Fri, 12 Jun 2015).") << "\n" << std::endl;
std::cout << _("Copyright by Jorge Barroso <jorge_barroso_11 at hotmail dot com>.") << std::endl;
std::cout << _("Distributed under GNU General Public License 2 (GPL 2.0)") << std::endl;
std::cout << _("Feel free to report any bug, issue or comment to https://github.com/jorge-barroso/baamanga") << std::endl;
}
