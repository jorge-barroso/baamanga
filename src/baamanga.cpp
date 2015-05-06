#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unistd.h>

using namespace std;

void domain_check(string, string);
void confdir_check(string);
void downdir_check(string);

void config(string);
void help();
void version();

void animea (string, string, string);
void danboru (string, string, string);
void ehentai (string, string, string);
void futahentai (string, string, string);
void mangafox (string, string, string);
void mangahere (string, string, string);
void mangareader (string, string, string);
void mangashare (string, string, string);
void pown (string, string, string);
void submanga (string, string, string);
void zerochan (string, string, string);

int main(int argc, char *argv[]) {
ifstream conf;
ifstream config_file;
string url, downdir, confdir = getenv("HOME");
//string config_file = ;


    confdir.append ("/.config/baamanga/");
    confdir_check(confdir);
    chdir(confdir.c_str());

    config_file.open("baamanga.conf", ios::binary | ios::ate);
    if( !config_file || config_file.tellg() < 20) {
        cout << "Configuration file does not exist. Please, wait a second and configure Baamanga." << endl;
        cout << "\n";
        config(confdir);
    }

    conf.open("baamanga.conf");
    getline(conf, downdir);
    conf.close();

    downdir = downdir.substr(downdir.find_last_of("=") +1);

    downdir_check(downdir);

    chdir(downdir.c_str());

    if (argc == 1){

        do {

            cout << "Welcome to Baamanga, the new manga downloader with lots of supported webpages." << endl;
            cout << "Just insert your download link and everything will be done automatically: ";
            getline(cin, url);

        }while(url.empty());

        domain_check(url, downdir);
}
    else if (argc == 2){
        if (strcmp(argv[1], "--config") == 0)
            config(confdir);

        else if (strcmp(argv[1], "--help") == 0)
            help();

        else if (strcmp(argv[1], "--version") == 0)
            version();

        else{
            url = argv[1];
            domain_check(url, downdir);
        }
}
    else if (argc > 2){
        short i;
        for (i=1;i <= argc; i++){
            url = argv[i];
            domain_check(url, downdir);
        }
    }

return 0;
}

void domain_check(string url, string downdir) {

string domain, url_orig, name;
size_t found, limit;

    url_orig = url;

    found = url.find("/") + 2;
    limit = url.find("/", found);
    domain = url.substr(found, limit - found);

if (domain.compare("manga.animea.net") == 0){						//ANIMEA
	cout << "\n" << "Manga from animea! I'd like to download it's anime aswell, soon maybe..." << endl;
	animea(url_orig, name, downdir);
	}
	else if (domain.compare("danbooru.donmai.us") == 0){			//DANBORU
			cout << "\n" << "Ok, you are downloading Danbooru boards, let's go"  << endl;
			danboru(url_orig, name, downdir);
		}
	else if (domain.compare(" e-hentai.org") == 0){					//E-HENTAI
			 cout << "\n" << "Wow, you are downloading manga from e-hentai, enjoy it!" << endl;
			ehentai(url_orig, name, downdir);
		}
	else if (domain.compare("futahentai.com") == 0){				//FUTAHENTAI
			 cout << "\n" << "Mmm Futahentai, having fun huh? Let's download it!" << endl;
			futahentai(url_orig, name, downdir);
		}
	else if (domain.compare("mangafox.me") == 0){					//MANGAFOX
			 cout << "\n" << "Mangafox! Good choice! Come on" << endl;
			mangafox(url_orig, name, downdir);
		}
	else if (domain.compare("es.mangahere.co") == 0){				//MANGAHERE
			 cout << "\n" << "This is a Mangahere url isn't it? It's a very good manga site, starting download!" << endl;
			mangahere(url_orig, name, downdir);
			}
	else if (domain.compare("www.mangareader.net") == 0){			//MANGAREADER
			 cout << "\n" << "Mmm mangareader, a classic! Good and varied, let's download it!" << endl;
			mangareader(url_orig, name, downdir);
		}
	else if (domain.compare("read.mangashare.com") == 0){			//MANGASHARE
			 cout << "\n" << "Shared manga is better isn't it? Starting download" << endl;
			mangashare(url_orig, name, downdir);
		}
	else if (domain.compare("www.pown.it") == 0){					//POWN
			 cout << "\n" << "Yeah good pown, let's share it" << endl;
			pown(url_orig, name, downdir);
		}
	else if (domain.compare("submanga.com") == 0 ){					//SUBMANGA
			 cout << "\n" << "This is Submanga! The best Spanish manga site!" << endl;
			submanga(url_orig, name, downdir);
		}
	else if (domain.compare("www.zerochan.net") == 0){			//ZEROCHAN
			 cout << "\n" << "Hey, good manga board, it is from Zerochan isn't it? Downloading!" << endl;
			zerochan(url_orig, name, downdir);
		}
	else
			 cout << "\n" << "Sorry, is not possible to download from this webpage, try with one bellow:\n-Submanga\n-Mcanime\n-Mangafox\n-Mangashare\n-Mangareader\n-Futahentai\n-E-hentai\n-4Chan\n-Zerochan\n-Danboru\n-Pown" << endl;

}
