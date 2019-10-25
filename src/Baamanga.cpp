#include <iostream>
#include <string>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include "services.h"
#include "BmHelpers.h"
#include "DirsChecks.h"
#include "Properties.h"

namespace fs = boost::filesystem;

const char * CONFIG_FILE_NAME = "baamanga.conf";

void domain_check(const std::string&, const std::string&);

int main(int argc, char *argv[]) {

    const std::string configurationPath {std::string(getenv("HOME")).append("/.config/baamanga")};
    fs::path confdir(configurationPath);

    DirsChecks::confdir_check(confdir);
    fs::current_path(confdir);

    std::ifstream config_file(CONFIG_FILE_NAME, std::ios::binary | std::ios::ate);

    if( !config_file || config_file.tellg() < 20) {
        std::cout << "Configuration file does not exist. Please, wait a second and configure Baamanga." << std::endl;
        std::cout << "\n";
        BmHelpers::config(confdir);
        std::cout << "\n";
    }
    config_file.close();

    //TODO rethink all the config logic up until here
    Properties prop(CONFIG_FILE_NAME);

    std::string downloadDir {prop.get((std::string &) "downdir")};

    DirsChecks::downdir_check(downloadDir);

    fs::current_path(downloadDir);

    std::string url;
    if (argc == 1){

        do {

            std::cout << "Welcome to Baamanga, the new manga downloader with lots of supported webpages." << std::endl;
            std::cout << "Just insert your download link and everything will be done automatically: ";
            std::ws(std::cin);
            getline(std::cin, url);

        }while(url.empty());
        fs::current_path(downloadDir);
        domain_check(url, downloadDir);
    }
    else if (argc == 2){
            fs::current_path(downloadDir);
        if (strcmp(argv[1], "config") == 0)
            BmHelpers::config(confdir);

        else if (strcmp(argv[1], "help") == 0)
            BmHelpers::displayHelp();

        else if (strcmp(argv[1], "version") == 0)
            BmHelpers::displayVersion();

        else{
            url = argv[1];
            domain_check(url, downloadDir);
        }
}
    else if (argc > 2){
        for (int i=1 ; i<= argc ; i++){
            url = argv[i];
            domain_check(url, downloadDir);
        }
    }

return 0;
}

void domain_check(const std::string& url, const std::string& downdir) {

std::string domain, name;
size_t found, limit;

    found = url.find('/') + 2;
    limit = url.find('/', found);
    domain = url.substr(found, limit - found);

    /*if (domain == "manga.animea.net"){						//ANIMEA
        std::cout << "\n" << "Manga from animea! I'd like to download it's anime aswell, soon maybe..." << std::endl;
        animea(url, name, downdir);
	}
    else if (domain == "danbooru.donmai.us"){			//DANBORU
			std::cout << "\n" << "Ok, you are downloading Danbooru boards, let's go"  << std::endl;
			danbooru(url, name, downdir);
		}
    else if (domain == " e-hentai.org"){					//E-HENTAI
			std::cout << "\n" << "Wow, you are downloading manga from e-hentai, enjoy it!" << std::endl;
			ehentai(url, name, downdir);
		}
    else if (domain == "futahentai.com" || domain == "www.futahentai.com"){				//FUTAHENTAI
			std::cout << "\n" << "Mmm Futahentai, having fun huh? Let's download it!" << std::endl;
			futahentai(url, name, downdir);
		}
    else if (domain == "mangaeden.com" || domain == "www.mangaeden.com"){				//MANGAEDEN
			std::cout << "\n" << "Manga Eden! To download English and Italian manga, a good one." << std::endl;
			mangaeden(url, name, downdir);
		}
    else if (domain == "mangafox.me"){					//MANGAFOX
            std::cout << "\n" << "Mangafox! Good choice! Come on" << std::endl;
            mangafox(url, name, downdir);
        }
    else if (domain == "mangahead.com" || domain == "www.mangahead.com"){					//MANGAFOX
            std::cout << "\n" << "Mangahead! You can also download Japanese and French manga here, not only in English!" << std::endl;
            mangahead(url, name, downdir);
    }
    else if (domain == "es.mangahere.co"){				//MANGAHERE
            std::cout << "\n" << "This is a Mangahere url isn't it? It's a very good manga site, starting download!" << std::endl;
            mangahere(url, name, downdir);
            }
    else if (domain == "www.mangareader.net"){			//MANGAREADER
            std::cout << "\n" << "Mmm mangareader, a classic! Good and varied, let's download it!" << std::endl;
            mangareader(url, name, downdir);
        }
    else if (domain == "read.mangashare.com"){			//MANGASHARE
            std::cout << "\n" << "Shared manga is better isn't it? Starting download" << std::endl;
            mangashare(url, name, downdir);
        }
    else if (domain == "www.pown.it"){					//POWN
            std::cout << "\n" << "Yeah good pown, let's share it" << std::endl;
            pown(url, name, downdir);
        }
    else if (domain == "submanga.com" ){					//SUBMANGA
            std::cout << "\n" << "This is Submanga! The best Spanish manga site!" << std::endl;
            submanga(url, name, downdir);
        }
    else if (domain == "wiemanga.com" || domain == "www.wiemanga.com"){					//SUBMANGA
            std::cout << "\n" << "Wie Manga! The best German manga site!" << std::endl;
            wiemanga(url, name, downdir);
        }
    else if (domain == "www.zerochan.net"){			//ZEROCHAN
            std::cout << "\n" << "Hey, good manga board, it is from Zerochan isn't it? Downloading!" << std::endl;
            zerochan(url, name, downdir);
        }
    else{*/
            std::cout << "\n" << "Sorry, is not possible to download from this webpage, try with one bellow:" << std::endl;
            ///std::cout << "-Animea" << std::endl;
            std::cout << "-Danbooru" << std::endl;
            ///std::cout << "-E-hentai" << std::endl;
            ///std::cout << "-Futahentai" << std::endl;
            ///std::cout << "-Mangaeden" << std::endl;
            std::cout << "-Mangafox" << std::endl;
            ///std::cout << "-Mangahead" << std::endl;
			///std::cout << "-Mangahere" << std::endl;
			std::cout << "-Mangareader" << std::endl;
			///std::cout << "-Mangashare" << std::endl;
			///std::cout << "-Pown" << std::endl;
			std::cout << "-Submanga" << std::endl;
			///std::cout << "-Wiemanga" << std::endl;
			///std::cout << "-Zerochan" << std::endl;
	//}
}
