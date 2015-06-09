#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "download.h"
#include "strings.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)
namespace fs = boost::filesystem;

void downdir_check(std::string);
void namedir_check(std::string, std::string);
void chapdir_check(std::string, std::string);
void mangareadersingle(std::string, std::string, std::string, std::string, std::string, bool);
void mangareaderbulk(std::string, std::string, std::string, std::string, std::string, std::string, std::string, bool);

void mangareader(std::string url, std::string name, std::string downdir){
    unsigned short j=0, len, slash = 0;
    std::string chapter, nameorig,code, chapname;
    bool mode;
    size_t found, limit;

    //Name parsing
    for(j=0;j<url.length();j++){
        if (url.at(j) == '/')
            slash++;
    }

    if (slash == 4)
        mode=false;
    if (slash == 5)
        mode=true;
		//"long" kind of URL,  extract code
		found = url.find("/", 9) + 1;
        limit = url.find("/", found);
    if (mode == true || (url.find(".html") != std::string::npos) == true){
        code = url.substr(found, limit - found);
        found = limit + 1;
        limit = url.find("/", found);
    }
    name = url.substr(found, limit - found);
    nameorig = name;
	//formating name

	name = repair(name);

	//Final formating and function choose
	len = name.length();

	if (name.at(len-5) == '.' || slash == 3){	//Bulk download
        if (mode == false){	//remove ".html" of long, bulk URL
            name = name.substr(0, name.find("."));
            nameorig = nameorig.substr(0, nameorig.find("."));
        }
        //Start Bulk
	std::cout << "\n\t" << _("Name: ") << name << std::endl;
	mangareaderbulk(url, name, nameorig, chapname, chapter, code, downdir, mode);
	}
  //Single chapter, long URL download
	else if (mode == true){
        found = url.find("-", limit) + 1;
        limit = url.find(".", found);
        chapter = url.substr(found, limit - found);
        std::cout << "\n\t" << _("Name: ") << name << std::endl;
        std::cout << "\t" << _("Chapter: ") << chapter << std::endl;
        mangareadersingle(url, name, nameorig, chapter, downdir, mode);
	}
    //Single chapter, short URL download
    else if (mode == false){
        chapter = url.substr(limit + 1);
        std::cout << "\n\t" << _("Name: ") << name << std::endl;
        std::cout << "\t" << _("Chapter: ") << chapter << std::endl;
        mangareadersingle(url, name, nameorig, chapter, downdir,mode);
    }
}

void mangareadersingle(std::string url, std::string name, std::string nameorig, std::string chapter, std::string downdir, bool mode){

	std::fstream fp;
	std::ofstream img;

std::stringstream ss;
bool err = false, result = false, pgfound = false;
short i=1, length;
std::string urldown, code, imgname, html, pageurl;
std::string tmpfile="/tmp/.html-mangareader-";
std::string baseurl	="http://www.mangareader.net/";
size_t found, limit;
	//to allow multiple instances of baamanga, one file per Manga
	tmpfile.append (name, 0, name.find(" "));

	//make directory
	namedir_check(name, downdir);
	downdir.append ("/" + name);
	chapdir_check(chapter, downdir);
	downdir.append ("/" + chapter);

    downdir_check(downdir);
	fs::current_path(downdir);

    //urldown for long url system
    if(mode == true){
        found = url.find ("/", 9) + 1;
        limit = url.find ("/", found);
        code = url.substr(found, limit - found - 1);
    }
    //urldown for short url system
    else if (mode == false)
        code = "/" + nameorig + "/" + chapter + "/";

	while (err == false){
		//restart "result" and "pgfound" values
		result		= false;
		pgfound		= false;

        ss.str("");
		ss << i;
        if (i < 10)
            imgname = "00" + ss.str() + ".jpg";
        else if (i < 100)
            imgname = "0" + ss.str() + ".jpg";
        ss.str("");
		i++;
        ss << i;
		urldown = code + ss.str();
		i--;
		/* Download html page*/
		url_download(url,tmpfile, fp);

    fp.open(tmpfile, std::fstream::in);
    while (std::getline(fp, html) && result == false){
		if ((html.find (urldown) != std::string::npos) == true){
            if (mode == true){
                found = html.find(urldown);
                limit = html.find("\'", found);
                url = baseurl + (html.substr(found, limit - found));
            }


            else if (mode == false){
                if (i > 1){
                    while(url.back() != '/'){
                        url.erase(url.find_last_of(url.back()));
                        length--;
                    }
                }
                else
                    url.append ("/" + ss.str());
            }
            result = true;
	}
    }

	fp.seekg(0);

	if (result == false)
		err = true;

	while (std::getline(fp, html)){
		if ((html.find("http:") != std::string::npos) == true && (html.find(nameorig) != std::string::npos) == true && (html.find(".jpg") != std::string::npos) == true){
			found = html.find("http:");
			limit = html.find ("\"", found);
			pageurl = html.substr(found, limit - found);
			pgfound	= true;
	    }
	}

	fp.close();

	if (pgfound == true){
		std::cout << "\n\n\n";
		std::cout << _("Downloading page ") << i << "..." << std::endl;
		pic_download(pageurl, imgname, img);
    }

	i++;
	}

	if (i > 2)
		std::cout << "\n\n";
		std::cout << name << _(" chapter ") << chapter << _(" downloaded.") << std::endl;

	fs::remove(tmpfile);

return;
}

void mangareaderbulk(std::string url, std::string name, std::string nameorig, std::string chapname, std::string chapter, std::string code, std::string downdir, bool mode){
    std::fstream bf;

std::stringstream ss;
short chapters=0, i=0, z=0;
std::string blkhtml, path2, path, downdir_orig;
std::string blktmpfile="/tmp/.baamanga-bulk-mangareader";
bool match = false;
char yesno;
size_t found, limit;

    //backup
    downdir_orig = downdir;

    //Default path 1
    path = nameorig + "/" + "1\""; // adding \" to avoid i.e. "chapter-13" as first coincidence
    //Default path 2
    path2 = nameorig + "/" + "chapter-1.html\""; // adding \" to avoid i.e. "chapter-13" as first coincidence
    //Download html
    url_download(url, blktmpfile, bf);
    //Count Chapters
    bf.open(blktmpfile, std::fstream::in);
    while (std::getline(bf, blkhtml)){
            //look for the path: style 1
            if ((blkhtml.find(path) != std::string::npos) == true && (blkhtml.find("chapter") != std::string::npos) == false){
                path = nameorig + "/";
                //Default path 2
                path2 = nameorig + "/" + "chapter-";
                chapters++;
            }
            //Look for path style: 2
            else if ((blkhtml.find(path2) != std::string::npos) == true && (blkhtml.find(code) != std::string::npos) == true){
                path = nameorig + "/";
                //Default path 2
                path2 = nameorig + "/" + "chapter-";

                chapters++;
            }
        }
    bf.close();

    //Ask for the first chapter to download for. Take 1 if not specified
    std::cout << "\n" << _("There are ") << chapters << _(" chapters, do you want to start downloading with some chapter in particular? [y/N] ");
		std::cin.get(yesno);

    if(yesno == 'y' || yesno == 'Y'){
        std::cout << _("Which chapter do you want to start for? ");
        std::cin >> i;
    }
    else
        i=1;

    if (i > chapters){
        std::cout << _("The chosed chapter does not exist, downloading from chapter 1") << std::endl;
        i = 1;
    }
    z = i;
    //Check if given chapter exists. Program takes next chapter in case the given one doesn't exist
    while(match==false){
        ss.str("");
        ss << i;
        while(path.back() != '/'){
            path.erase(path.find_last_of(path.back()));
        }
        path.append(ss.str() + "\"");// adding \" to avoid i.e. "13" as first coincidence
        while(path2.back() != '-'){
            path2.erase(path2.find_last_of(path2.back()));
        }
        path2.append(ss. str() + ".html\""); // adding \" to avoid i.e. "chapter-13" as first coincidence
        bf.open(blktmpfile, std::fstream::in);
        while (std::getline(bf, blkhtml)){
            if ((blkhtml.find(path) != std::string::npos) == true && (blkhtml.find("chapter") != std::string::npos) == false){
                match=true;
            }
            if ((blkhtml.find(path2) != std::string::npos) == true && (blkhtml.find(code) != std::string::npos) == true){
                match=true;
            }
        }
        bf.close();
        if (match==false){
            bf.seekg(0);
            i++;
        }
    }
    bf.seekg(0);

    if (z != i)
        std::cout << _("Given chapter does not exist. Download will start from next available chapter (Chapter n. ") << i << ")" << std::endl;

    if(i > 1){
        //Look for chapter one (avoids find the chapter on "recents" list, which will cause problems)
        while(path.back() != '/'){
            path.erase(path.find_last_of(path.back()));
        }
        path.append("1\"");
        while(path2.back() != '-'){
            path2.erase(path2.find_last_of(path2.back()));
        }
        path2.append("1.html\"");

        match = false;

        bf.open(blktmpfile, std::fstream::in);
        while (std::getline(bf, blkhtml) && match == false){
            if ((blkhtml.find(path) != std::string::npos) == true && (blkhtml.find("chapter") != std::string::npos) == false){
                while(path.back() != '/'){
                    path.erase(path.find_last_of(path.back()));
                }
                while(path2.back() != '-'){
                    path2.erase(path2.find_last_of(path2.back()));
                }
                match = true;
            }
            if ((blkhtml.find(path2) != std::string::npos) == true && (blkhtml.find(code) != std::string::npos) == true){
                while(path.back() != '/'){
                    path.erase(path.find_last_of(path.back()));
                }
                while(path2.back() != '-'){
                    path2.erase(path2.find_last_of(path2.back()));
                }
                match = true;
            }
        }
    }
    bf.close();

    //Download begins
    if(i > 1){
    path.append(ss.str());
    path2.append(ss.str() + ".html");;
    }

    bf.open(blktmpfile, std::fstream::in);
    while (std::getline(bf, blkhtml)){
        if ((blkhtml.find(path) != std::string::npos) == true && (blkhtml.find("chapter") != std::string::npos) == false){
            mode = false;
            found = blkhtml.find(path);
            limit = blkhtml.find("\"", found);
            url = "http://www.mangareader.net/" + blkhtml.substr(found, limit - found);
            chapter = url.substr(url.find_last_of("/") + 1);
            //chapter.erase(0);
            std::cout << "\n\t" << _("Chapter: ") << chapter << std::endl;
            mangareadersingle(url, name, nameorig, chapter, downdir, mode);
            while(path.back() != '/'){
                path.erase(path.find_last_of(path.back()));
            }
            while(path2.back() != '-'){
                path2.erase(path2.find_last_of(path2.back()));
            }
            downdir = downdir_orig;
		}

        if ((blkhtml.find(path2) != std::string::npos) == true && (blkhtml.find(code) != std::string::npos) == false){
            mode = true;
            found = blkhtml.find("\"") + 1;
            limit = blkhtml.find("\"", found);
            url = "http://www.mangareader.net" + blkhtml.substr(found, limit - found);
            found = url.find_last_of("-") + 1;
            limit = url.find(".", found);
            chapter = url.substr(found, limit - found);
            std::cout << "\n\t" << _("Chapter: ") << chapter << std::endl;
            mangareadersingle(url, name, nameorig, chapter, downdir, mode);
            while(path.back() != '/'){
                path.erase(path.find_last_of(path.back()));
            }
            while(path2.back() != '-'){
                path2.erase(path2.find_last_of(path2.back()));
            }
            downdir = downdir_orig;
        }
    }
	bf.close();
	fs::remove(blktmpfile);
    std::cout << "\n\t" << _("Download Finished") << std::endl;

return;
}
