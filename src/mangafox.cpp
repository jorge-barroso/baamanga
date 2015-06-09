#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "strings.h"
#include "download.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)
namespace fs = boost::filesystem;

void downdir_check(std::string);
void namedir_check(std::string, std::string);
void chapdir_check(std::string, std::string);
void mangafoxsingle(std::string, std::string, std::string, std::string, std::string);
void mangafoxbulk(std::string, std::string, std::string, std::string);

void mangafox(std::string url, std::string name, std::string downdir){
short unsigned l=0, slash=0;
std::string discr, chapter, volume, nameorig;
size_t found = 0, limit = 0;
bool mode;

    for(l=0;l<url.length();l++){
        if (url.at(l) == '/')
            slash++;
    }

    if (slash < 6)
        mode=false;
    if (slash >= 6)
        mode=true;

    //Let's parse the name
    if (mode==false){
        if (url.back() == '/')
            url.erase(url.length() - 1);
        found = url.find_last_of("/") + 1;
        name = url.substr(found);
    }
    else{
        found = url.find("/", url.find("/manga/") + 1) + 1;
        limit = url.find("/", found);
        name = url.substr(found, limit - found);
    }
    nameorig = name;

    name = repair(name);

    if(mode == false){
        std::cout << "\n\t" << _("Name: ") << name << std::endl;
		mangafoxbulk(name, nameorig, url, downdir);
	}
	else{
        //Now for the chapter
        found = limit + 1;
        limit = url.find ("/", found);
        discr = url.substr(found, limit - found);
		if (discr.at(0) != 'c'){
            volume = discr;
            found = limit + 1;
            limit = url.find ("/", found);
            chapter= url.substr(found, limit - found);    //it is a chapter, but this is the volume serial name
		}
		else
			chapter = discr;
		while ((chapter.at(0) == 'c' || chapter.at(0) == '0') && chapter.length() > 1)
			chapter.erase(chapter.begin());
		std::cout << "\n";
		std::cout << "\t" << _("Name: ") << name << std::endl;
		std::cout << "\t" << _("Chapter: ") << chapter << std::endl;
		mangafoxsingle(url, name, chapter, volume, downdir);
	}
}

void mangafoxsingle(std::string url, std::string name, std::string chapter, std::string volume, std::string downdir){

	std::fstream fp;
	std::ofstream img;

std::stringstream ss;
short i=1, k=0;
size_t found, limit;
bool err=false, result, pgfound;
std::string urldown;
std::string pgbase = "http://a.mfcdn.net/store/manga/";
std::string tmpfile = "/tmp/.html-mangafox";
std::string html, imgname, pageurl;

	tmpfile.append(name, 0, 10);

	namedir_check	(name, downdir);
	downdir.append ("/" + name);
	if (!volume.empty()){
        downdir.append ("/" + volume);
        downdir_check (downdir);
	}
	chapdir_check	(chapter, downdir);
	downdir.append ("/" + chapter);
	fs::current_path(downdir);

	do{
		result = false;
		pgfound = false;

        ss.str("");
        ss << ++k;
		if (k < 10)
            imgname = "00" + ss.str() + ".jpg";
        else if (i < 100)
            imgname = "0" + ss.str() + ".jpg";
        else
            imgname = ss.str() + ".jpg";
        ss.str("");
        ss << ++i;
            urldown = ss.str() + ".html";
        i--, k--;

		/* Download html page*/
		url_download(url, tmpfile, fp);

	/* HERE STARTS HTML PARSING OF THE FILE */
	/* Look for the next html page to download */
        fp.open(tmpfile, std::fstream::in);
        while ( std::getline(fp, html) && result == false){
            if ((html.find(urldown) != std::string::npos) == true){
                url = url.substr(0, url.find_last_of("/") + 1) + urldown;
                result++;
            }
        }
        fp.close();

        /* HERE WE GET THE PAGE URL */
        fp.open(tmpfile, std::fstream::in);
        while (std::getline(fp, html) && pgfound == false){
            if ((html.find("") != std::string::npos) == true && (html.find("compressed") != std::string::npos) == true && pgfound == false) {
                found = html.find(pgbase);
                limit = html.find("\"", found);
                pageurl = html.substr(found, limit - found);
                pgfound = true;
            }
        }

        fp.close();
        if (pgfound == true){
            std::cout << "\n\n";
            std::cout << _("Downloading page ") << i << "..." << std::endl;

            pic_download(pageurl, imgname, img);

        if (result == false)
            err = true;
        }

        i++,k++;

	}while(err == false);

	if (i > 2){
		std::cout << "\n" << std::endl;
		std::cout << name << _(" chapter ") << chapter << _(" downloaded.") << std::endl;
	}
}

void mangafoxbulk(std::string name, std::string nameorig, std::string url, std::string downdir){
    std::fstream bf;

std::stringstream ss;
std::string blkhtml, chapter;
std::string path="http://mangafox.me/manga/";
std::string blktmpfile="/tmp/.baamanga-bulk-mangafox";
short chapters=0, i, z;
char yesno;
bool match=false, zero;
size_t found, limit;

    path.append (nameorig + "/");

    url_download(url, blktmpfile, bf);

    bf.open(blktmpfile, std::fstream::in);
    while (std::getline(bf, blkhtml)){
            if ((blkhtml.find(path) != std::string::npos) == true && (blkhtml.find("1.html") != std::string::npos) == true){
                chapters++;
                if ((blkhtml.find("c000") != std::string::npos) == true)
                    zero = true;

            }
    }
    bf.close();

    //Ask for the first chapter to download for. Take 1 if not specified
    std::cout << "\n";
    if (zero == 1)
        std::cout << "\n" << _("This manga has a \"Chapter 0\"") << std::endl;
    std::cout << _("There are ") << chapters << _(" chapters, do you want to start downloading with some chapter in particular? [y/N] ");

    std::cin.get (yesno);

    if(yesno == 'y' || yesno == 'Y'){
        std::cout << _("Which chapter do you want to start for? ");
        std::cin >> i;
    }
    else
        if (zero == true)
            i=0;
        else
            i=1;
    if (i > chapters){
            if (zero == false)
                std::cout << _("The chosen chapter does not exist, downloading from chapter 1") << std::endl;
            if (zero == true)
                std::cout << _("The chosen chapter does not exist, downloading from chapter 0") << std::endl;
    }
    z = i;

    do{
        ss << i;
        if (i < 10)
            chapter = "c00" + ss.str() + "/1.html";
        else if (i < 100)
            chapter = "c0" + ss.str() + "/1.html";
        else
            chapter = ss.str() + "/1.html";
        ss.str("");
        bf.open(blktmpfile, std::fstream::in);
        while (std::getline(bf, blkhtml) && match == false){
            if((blkhtml.find(chapter) != std::string::npos) == true)
                match=1;
        }
        bf.close();
        if (match == false)
            ++i;
    }while(match==false);

    if (z != i)
        std::cout << _("Given chapter does not exist. Download will start from next available chapter (Chapter n. ") << i << std::endl;

    for (;i<=chapters;i++){
        ss << i;
        if (i < 10)
            chapter = "c00" + ss.str() + "/1.html";
        else if (i < 100)
            chapter = "c0" + ss.str() + "/1.html";
        else
            chapter = ss.str() + "/1.html";
        ss.str("");

        bf.open(blktmpfile, std::fstream::in);
        while(std::getline(bf, blkhtml)){
            if((blkhtml.find(chapter) != std::string::npos) == true){
                found = blkhtml.find(path);
				limit = blkhtml.find("\"", found);
				url = blkhtml.substr(found, limit - found);
                mangafox(url, name, downdir);
            }
        }
        bf.close();
    }

return;
}
