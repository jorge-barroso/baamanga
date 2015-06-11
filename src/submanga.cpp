#include <iostream>
#include <climits>
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

void submangasingle(std::string, std::string, std::string, std::string);
void submangabulk(std::string, std::string, std::string, std::string, std::string);
void namedir_check(std::string, std::string);
void chapdir_check(std::string, std::string);

void submanga(std::string url, std::string name, std::string downdir){
	//short unsigned j;
	size_t found, limit;
	std::string discr, chapter, nameorig;

    found = url.find("/", 9) + 1;
	limit = url.find("/", found);
	name = url.substr(found, limit-found);
    nameorig = name;
	// Parse name
	name = normalize(name);
	found = limit + 1;
	limit = url.find("/", found);
	discr = url.substr(found, limit-found);

	if ((url.find("completa") != std::string::npos) == 1){
		submangabulk(url, name, nameorig, chapter, downdir);
	}
	else{
		chapter = discr;
		std::cout << "\n";
		std::cout << "\t" << _("Name: ") << name << std::endl;
		std::cout << "\t" << _("Chapter: ") << chapter << std::endl;
		submangasingle(url, name, chapter, downdir);
	}
  return;
}

void submangasingle(std::string url, std::string name, std::string chapter, std::string downdir){

	std::fstream fp;
	std::ofstream img;
std::stringstream ss;
bool err = false, imgfound = false, pgfound = false;
std::string urldown, pageurl, code;
const std::string pgbaseone = "http://omg.submanga.com/pages";
const std::string pgbasetwo = "http://img.submanga.com/pages";
const std::string pgbasethree = "http://amg.submanga.com/pages";
const std::string pgbasefour = "http://img2.submanga.com/pages";
std::string tmpfile = "/tmp/.html-submanga";
std::string imgname, html;
short i=1, k=0, mode = 0;
size_t found, limit;

	tmpfile.append (name, 0, 10);

	namedir_check	(name, downdir);
	downdir.append ("/" + name);
	chapdir_check	(chapter, downdir);
	downdir.append("/" + chapter);
	fs::current_path(downdir);

    code = url.substr(url.find_last_of("/") + 1);

	do{
		pgfound = 0;
		imgfound = 0;
		ss << i;
		urldown = "http://submanga.com/c/" + code;
        if (i > 1)
            urldown.append("/" + ss.str());
        ss.str("");

        ss << k;
		if (k < 100)
            imgname = "0" + ss.str() + ".jpg";
        if (i < 10)
            imgname = "00" + ss.str() + ".jpg";
        ss.str("");

		/* Download html page*/
		url_download(url, tmpfile, fp);

	/* HERE STARTS HTML PARSING OF THE FILE */


		/* Look for the next html page to download */
        fp.open(tmpfile, std::fstream::in);
		while (getline(fp, html)){
			if ((html.find(urldown) != std::string::npos) == 1){
                    url = urldown;
					pgfound++;
				}
			}
        fp.close();

		if (pgfound == 0)
			err = 1;

		/* HERE WE GET THE PAGE URL */

		if (i>1){
			if (mode == 0){ //omg.submanga.com
                fp.open(tmpfile, std::fstream::in);
				while (getline(fp, html)){
					if ((html.find(pgbaseone) != std::string::npos) == 1){
						found = html.find(pgbaseone);
						limit = html.find("\"", found);
						pageurl = html.substr(found, limit - found);
						imgfound = 1;
					}
				}
                fp.close();
			}

			if (imgfound == 0 && i == 2)
				mode = 1;

			if (mode == 1){ //img.submanga.com
                fp.open(tmpfile, std::fstream::in);
				while (getline(fp, html)){
					if ((html.find(pgbasetwo) != std::string::npos) == 1){
						found = html.find(pgbasetwo);
						limit = html.find("\"", found);
						pageurl = html.substr(found, limit - found);
						imgfound = 1;
					}
				}
                fp.close();
			}

			if (imgfound == 0 && i == 2)
				mode = 2;

			if (mode == 2){ //amg.submanga.com
                fp.open(tmpfile, std::fstream::in);
				while (getline(fp, html)){
					if ((html.find(pgbasethree) != std::string::npos) == 1){
						found = html.find(pgbasethree);
						limit = html.find("\"", found);
						pageurl = html.substr(found, limit - found);
						imgfound = 1;
					}
				}
                fp.close();
			}

			if (imgfound == 0 && i == 2)
				mode = 3;

			if (mode == 3){ //img2.submanga.com
                fp.open(tmpfile, std::fstream::in);
				while (getline(fp, html)){
					if ((html.find(pgbasefour) != std::string::npos) == 1){
						found = html.find(pgbasefour);
						limit = html.find("\"", found);
						pageurl = html.substr(found, limit - found);
						imgfound = 1;
					}
				}
            fp.close();
			}
		}

		if (i > 1 && imgfound == 1){
		/* Now for the image */

		std::cout << "\n\n";
		std::cout << _("Downloading page ") << k << "..." << std::endl;

        pic_download(url, imgname, img);
		}
		i++, k++;

	}while(err == 0);
	if (i > 2)
		std::cout << "\n\n";
		std::cout << name << _(" chapter ") << chapter << _(" downloaded.") << std::endl;
	fs::remove(tmpfile);

return;
}

void submangabulk(std::string url, std::string name, std::string nameorig, std::string chapter, std::string downdir){
std::fstream bf;
std::fstream spec;

std::stringstream ss;
short chapters=0, spchapters = 0, i, j;
std::string blkhtml, newest;
std::string blktmpfile= "/tmp/.baamanga-bulk-submanga";
std::string urldown = "http://submanga.com/";
size_t found, limit, foundspec = 0;
char spask;
bool check = 0, match = 0;

    urldown.append(nameorig + "/");

    url_download(url, blktmpfile, bf);

    bf.open(blktmpfile, std::fstream::in);
    spec.open("/tmp/.special_chapters", std::fstream::out);
    while(getline(bf, blkhtml)){
            found = 0;
        while((blkhtml.find(urldown, found) != std::string::npos) == 1){

            //delimit the found url
            found = blkhtml.find(urldown,found);
            limit = blkhtml.find("\"", found);

            //find the beggining of special chapters
            if ((blkhtml.find("Especiales") != std::string::npos) == 1)
                foundspec = blkhtml.find("Especiales");

            //check if is a regular or a special chapter
            if ((blkhtml.substr(found, limit - found).find("completa") != std::string::npos) == 0 && (blkhtml.substr(found, limit - found).find("scanlations") != std::string::npos) == 0 && (foundspec == 0 || found < foundspec))
                chapters++;
            else if (foundspec != 0 && found > foundspec){
                spchapters++;
                spec << blkhtml.substr(found, limit - found) << std::endl;
            }

            //check if there is chapter 0
            if ((blkhtml.substr(found, limit - found).find("/0/") != std::string::npos) == 1)
                check=1;

            //get newest chapter url, to get the higher chapter available
            if (chapters == 1)
                newest = blkhtml.substr(found, limit - found);

            //update found to continue looking for coincidences
            found=limit + 1;
            }
    }
    spec.close();
    bf.close();
    //get the latest chapter number
    found = newest.find("/", newest.find("/", 9) + 1) +1;
    limit = newest.find("/", found);
    newest = newest.substr(found, limit - found);

    //check whether it is complete and inform if it's not
    if(chapters < atoi(newest.c_str())){
        std::cout << "\n" << _("There are some missing chapters. ");
        std::cout << _("Latest chapter is ") << newest << _(", but there are ") << chapters << _(" available chapters.") << std::endl;
    }
    else
        std::cout << _("There are ") << chapters << _(" available chapters. ");

    //inform if there is a Chapter 0
    if (check == 1)
         std::cout << _("A \"Chapter 0\" was found.") << "\n" << std::endl;
    else
        std::cout << "\n" << std::endl;

    //inform of special chapters and ask to download them
    if (spchapters > 0){
        do{
            std::cout << "\n" << spchapters << _(" special chapters were found, do you want to download them? [Y/n/v(view)] ");
            std::cin.get(spask);
            std::cin.clear(); std::cin.ignore(INT_MAX,'\n');
            if (spask == 'v' || spask == 'v'){
                spec.open("/tmp/.special_chapters", std::fstream::in);
                while (getline(spec, blkhtml))
                    std::cout << blkhtml << std::endl;
                spec.close();
            }
        }while (spask != 'y' && spask != 'Y' && spask != 'n' && spask != 'N');
        std::cout << "\n" << _("Ok, now let's start downloading the regular chapters. ");
    }

    std::cout << _("Which chapter do you want to start for? ");
    std::cin >> i;
    j = i;

    if (i > atoi(newest.c_str())){
        if (check == 1)
            i = 0;
        else if (check == 0)
            i = 1;
        std::cout << _("Introduced chapter is higher than the biggest chapter of that manga, the download will start by the first available chapter (chapter n. ") << i << ")"<< std::endl;
        }
//check if chosen chapter exists
do{
    ss << i;
    urldown.append(ss.str() + "/");
    ss.str("");
    bf.open(blktmpfile, std::fstream::in);
    while (getline(bf, blkhtml))
        if ((blkhtml.find(urldown) != std::string::npos) == 1)
            match = 1;
    bf.close();

    do{
        urldown.erase(urldown.find_last_of(urldown.back()));
    }while(urldown.back() != '/');

    if (match==0)
        i++;
}while (match == 0);

//If chosen chapter is not available, inform which chapter will be downloaded (the next available)
if(j!=i)
    std::cout << _("Chapter ") << j << _("is not available, next available chapter will be downloaded (") << i << ")." << std::endl;

//Start download
for (;i<=atoi(newest.c_str());i++){
    ss << i;
    urldown.append(ss.str() + "/");
    ss.str("");
    bf.open(blktmpfile, std::fstream::in);
    while (getline(bf, blkhtml)){
        if ((blkhtml.find(urldown) != std::string::npos) == 1){
            found = blkhtml.find(urldown);
            limit = blkhtml.find("\"", found);
            url = blkhtml.substr(found, limit - found);
            submanga(url, name, downdir);
        }
    }
    bf.close();
    do{
        urldown.erase(urldown.find_last_of(urldown.back()));
    }while(urldown.back() != '/');
}

if (spask != 'n' && spask != 'N' && spask != 'v' && spask != 'V'){
    std::cout << "\n" << _("DOWNLOADING SPECIAL CHAPTERS:") << std::endl;
    spec.open("/tmp/.special_chapters", std::fstream::in);
    while(getline(spec, blkhtml)){
        url = blkhtml;
        submanga(url, name, downdir);
    }
}

std::cout << _("Every chapter has been successfully downloaded. Be back soon!") << std::endl;

return;
}
