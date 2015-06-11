#include <iostream>
#include <fstream>
#include <string>
#include "services.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)
namespace fs = boost::filesystem;

void domain_check(std::string, std::string);
void confdir_check(fs::path);
void downdir_check(std::string);

void config(fs::path);
void help();
void version();

int main(int argc, char *argv[]) {
fs::path confdir("/home/jorge/.config/baamanga");
std::ifstream config_file;
std::string url, downdir;

    setlocale (LC_ALL, "");
    textdomain ("baamanga");
    bindtextdomain ("baamanga", "/usr/share/locale");

    confdir_check(confdir);
    fs::current_path(confdir);

    config_file.open("baamanga.conf", std::ios::binary | std::ios::ate);

    if( !config_file || config_file.tellg() < 20) {
        std::cout << _("Configuration file does not exist. Please, wait a second and configure Baamanga.") << std::endl;
        std::cout << "\n";
        config(confdir);
        std::cout << "\n";
    }
    config_file.close();

    config_file.open("baamanga.conf", std::fstream::in);
    getline(config_file, downdir);
    config_file.close();

    downdir = downdir.substr(downdir.find_last_of("=") +1);

    downdir_check(downdir);

    fs::current_path(downdir);

    if (argc == 1){

        do {

            std::cout << _("Welcome to Baamanga, the new manga downloader with lots of supported webpages.") << std::endl;
            std::cout << _("Just insert your download link and everything will be done automatically: ");
            std::ws(std::cin);
            getline(std::cin, url);

        }while(url.empty());
        fs::current_path(downdir);
        domain_check(url, downdir);
    }
    else if (argc == 2){
            fs::current_path(downdir);
        if (strcmp(argv[1], "config") == 0)
            config(confdir);

        else if (strcmp(argv[1], "help") == 0)
            help();

        else if (strcmp(argv[1], "version") == 0)
            version();

        else{
            url = argv[1];
            domain_check(url, downdir);
        }
}
    else if (argc > 2){
        for (short i=1 ; i<= argc ; i++){
            url = argv[i];
            domain_check(url, downdir);
        }
    }

return 0;
}

void domain_check(std::string url, std::string downdir) {

std::string domain, name;
size_t found, limit;

    found = url.find("/") + 2;
    limit = url.find("/", found);
    domain = url.substr(found, limit - found);

if (domain.compare("manga.animea.net") == 0){						//ANIMEA
	std::cout << "\n" << _("Manga from animea! I'd like to download it's anime aswell, soon maybe...") << std::endl;
	animea(url, name, downdir);
	}
	else if (domain.compare("danbooru.donmai.us") == 0){			//DANBORU
			std::cout << "\n" << _("Ok, you are downloading Danbooru boards, let's go")  << std::endl;
			danbooru(url, name, downdir);
		}
	else if (domain.compare(" e-hentai.org") == 0){					//E-HENTAI
			std::cout << "\n" << _("Wow, you are downloading manga from e-hentai, enjoy it!") << std::endl;
			ehentai(url, name, downdir);
		}
	else if (domain.compare("futahentai.com") == 0 || domain.compare("www.futahentai.com") == 0){				//FUTAHENTAI
			std::cout << "\n" << _("Mmm Futahentai, having fun huh? Let's download it!") << std::endl;
			futahentai(url, name, downdir);
		}
	else if (domain.compare("mangaeden.com") == 0 || domain.compare("www.mangaeden.com") == 0){				//MANGAEDEN
			std::cout << "\n" << _("Manga Eden! To download English and Italian manga, a good one.") << std::endl;
			mangaeden(url, name, downdir);
		}
	else if (domain.compare("mangafox.me") == 0){					//MANGAFOX
            std::cout << "\n" << _("Mangafox! Good choice! Come on") << std::endl;
			mangafox(url, name, downdir);
		}
    else if (domain.compare("mangahead.com") == 0 || domain.compare("www.mangahead.com") == 0){					//MANGAFOX
            std::cout << "\n" << _("Mangahead! You can also download Japanese and French manga here, not only in English!") << std::endl;
            mangahead(url, name, downdir);
    }
	else if (domain.compare("es.mangahere.co") == 0){				//MANGAHERE
			std::cout << "\n" << _("This is a Mangahere url isn't it? It's a very good manga site, starting download!") << std::endl;
			mangahere(url, name, downdir);
			}
	else if (domain.compare("www.mangareader.net") == 0){			//MANGAREADER
			std::cout << "\n" << _("Mmm mangareader, a classic! Good and varied, let's download it!") << std::endl;
			mangareader(url, name, downdir);
		}
	else if (domain.compare("read.mangashare.com") == 0){			//MANGASHARE
			std::cout << "\n" << _("Shared manga is better isn't it? Starting download") << std::endl;
			mangashare(url, name, downdir);
		}
	else if (domain.compare("www.pown.it") == 0){					//POWN
			std::cout << "\n" << _("Yeah good pown, let's share it") << std::endl;
			pown(url, name, downdir);
		}
	else if (domain.compare("submanga.com") == 0 ){					//SUBMANGA
			std::cout << "\n" << _("This is Submanga! The best Spanish manga site!") << std::endl;
			submanga(url, name, downdir);
		}
	else if (domain.compare("wiemanga.com") == 0 || domain.compare("www.wiemanga.com") == 0){					//SUBMANGA
			std::cout << "\n" << _("Wie Manga! The best German manga site!") << std::endl;
			wiemanga(url, name, downdir);
		}
	else if (domain.compare("www.zerochan.net") == 0){			//ZEROCHAN
			std::cout << "\n" << _("Hey, good manga board, it is from Zerochan isn't it? Downloading!") << std::endl;
			zerochan(url, name, downdir);
		}
	else{
			std::cout << "\n" << _("Sorry, is not possible to download from this webpage, try with one bellow:") << std::endl;
			///std::cout << "-Animea" << std::endl;
			std::cout << "-Danbooru" << std::endl;
			///std::cout << "-E-hentai" << std::endl;
			///std::cout << "-Futahentai" << std::endl;
			///std::cout << "-Mangaeden" << std::endl;
			std::cout << "-Mangafox" << std::endl;;
			///std::cout << "-Mangahead" << std::endl;
			///std::cout << "-Mangahere" << std::endl;
			std::cout << "-Mangareader" << std::endl;
			///std::cout << "-Mangashare" << std::endl;
			///std::cout << "-Pown" << std::endl;
			std::cout << "-Submanga" << std::endl;
			///std::cout << "-Wiemanga" << std::endl;
			///std::cout << "-Zerochan" << std::endl;
	}
}
