#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include "download.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <libintl.h>
#include <locale.h>

#define _(string) gettext (string)
namespace fs = boost::filesystem;

void downdir_check(std::string);
void danboorudirect(std::string, std::string, std::string);
void danboorusingle(std::string, std::string, std::string);
void danboorubulk(std::string, std::string, std::string, bool);

void danbooru(std::string url, std::string name, std::string downdir){

    short unsigned slash = 0, j;
    std::string tag;
    bool popular = 0;
    size_t found;
    time_t now = time(0);
    char* dt = ctime(&now);

    downdir.append("/Danbooru");
    downdir_check(downdir);

    for (j=0;j < url.length();j++){
        if (url.at(j) == '/')
            slash++;
    }

	if ((url.find("posts") != std::string::npos) == 1){
		if ((url.find("/posts/") != std::string::npos) == 1 && slash == 4)
            danboorusingle(url, name, downdir);
        else{
            if ((url.find("/popular") != std::string::npos) == false){
                found = url.find("=", url.find("tags=")) + 1;
                tag = url.substr(found);
                if (tag == "order:rank" || tag == "orde%3Arank")
                    tag = "Hot";
                downdir.append("/" + tag);
                downdir_check(downdir);
                if (tag == "Hot"){
                    downdir.append("/");
                    downdir.append(dt);
                    downdir_check(downdir);
                }
                danboorubulk(url, name, downdir, popular);
            }
            else{
                downdir.append("/popular");
                downdir_check(downdir);
                popular = true;
                danboorubulk(url, name, downdir, popular);
            }
        }
    }
	else if ((url.find("data") != std::string::npos) == 1)
        danboorudirect(url, name, downdir);
}


void danboorudirect(std::string url, std::string name, std::string downdir){
    std::ofstream dp;

    if (name.empty()){
        std::cout << _("Select a name for your downloaded file: ");
        getline (std::cin, name);
    }

    fs::current_path(downdir);

    pic_download(url, name, dp);

}

void danboorusingle(std::string url, std::string name, std::string downdir){
    std::fstream fp;
    std::ofstream img;

std::string urldown = "http://danbooru.donmai.us/data/";
std::string tmpfile = "/tmp/.html-danbooru";
std::string html, boardurl;
size_t found, limit;

    fs::current_path(downdir);

    url_download(url, tmpfile, fp);

    if (name.empty()){
        std::cout << _("Give a name to the board: ");
        getline (std::cin, name);
    }

    fp.open(tmpfile, std::fstream::in);
    while(getline(fp, html)){
        if ((html.find(urldown) != std::string::npos) == 1){
            found = html.find(urldown);
            limit = html.find ("\"", found);
            boardurl = html.substr(found, limit - found);
        }
    }
    fp.close();

        pic_download(boardurl, name, img);

        std::cout << "*******************************************";
        std::cout << "*******************************************" << std::endl;
        std::cout << _("Download of ") << name << _(" finished") << std::endl;

return;
}

void danboorubulk(std::string url, std::string name, std::string downdir, bool popular){
    std::fstream fp;

std::stringstream ss;
std::string blktmpfile = "/tmp/.baamanga-bulk-danbooru";
std::string blkurldown = "data-large-file-url";
std::string page, blkhtml, popular_folder, pageurl;
short unsigned i=1, j=2;
bool imgfound = 0, err=0;
size_t found, limit;

    do{
        url_download(url, blktmpfile, fp);

        if (popular == true){
            fp.open(blktmpfile, std::fstream::in);
            while(getline(fp, blkhtml)){
                if ((blkhtml.find("Popular: ") != std::string::npos) == 1){
                    found = blkhtml.find("Popular: ") + 9;
                    limit = blkhtml.find ("<", found);
                    popular_folder = blkhtml.substr(found, limit - found);
                    downdir.append("/" + popular_folder);
                    downdir_check(downdir);
                }
            }
            fp.close();
        }
        fp.open(blktmpfile, std::fstream::in);
        while(getline(fp, blkhtml)){
            //find next gallery
            if ((blkhtml.find(blkurldown) != std::string::npos) == true){
                found = blkhtml.find("\"") + 1;
                limit = blkhtml.find ("\"", found);
                url = "http://danbooru.donmai.us" + blkhtml.substr(found, limit - found);
                ss << i;
                name = ss.str();
                std::cout << "\n\n" << _("Downloading board n.") << name << "..." << std::endl;
                danboorudirect(url, name, downdir);
                i++;
                ss.str("");
            }
        }
        fp.close();

        ss << j;
        page = "/posts?page=" + ss.str();
        ss.str("");

        fp.open(blktmpfile, std::fstream::in);
        while(getline(fp, blkhtml)){
            //find image
        if ((blkhtml.find(page) != std::string::npos) == true && popular == false){
            found = blkhtml.find(page);
            limit = blkhtml.find ("\"", found);
            url = "http://danbooru.donmai.us" + blkhtml.substr(found, limit - found);
            imgfound = 1;
            }
        }
        fp.close();

        if (imgfound == 0)
            err = 1;
        else
            j++;
    }while (err==0);

    fs::remove (blktmpfile);
return;
}
