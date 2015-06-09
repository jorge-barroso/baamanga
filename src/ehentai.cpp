#include <iostream>
#include <string>
#include "strings.h"
#include "download.h"
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)

void ehentai(std::string url, std::string name, std::string downdir){
std::cout << _("This is ehentai") << std::endl;
}
