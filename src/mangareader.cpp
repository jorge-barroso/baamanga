#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <curlcpp/curl_easy.h>
#include <unistd.h>

using namespace std;

void downdir_check(string);
void namedir_check(string, string);
void chapdir_check(string, string);
void mangareadersingle(string, string, string, string, string, bool);
void mangareaderbulk(string, string, string, string, string, string, string, bool);

void mangareader(string url, string name, string downdir){
    unsigned short j=0, len, slash = 0;
    string chapter, nameorig,code, chapname;
    bool mode;
    size_t found, limit;

    //Name parsing
    for(j=0;j<url.length();j++){
        if (url.at(j) == '/')
            slash++;
    }

    if (slash == 4)
        mode=0;
    if (slash == 5)
        mode=1;
		//"long" kind of URL,  extract code
		found = url.find("/", 9) + 1;
        limit = url.find("/", found);
    if (mode == 1 || (url.find(".html") != string::npos) == 1){
        code = url.substr(found, limit - found);
        found = limit + 1;
        limit = url.find("/", found);
    }
    name = url.substr(found, limit - found);
    nameorig = name;
	//formating name
	for (j=1;j<name.length();j++){
        if(name.at(j) == '-')
        	name.at(j) = ' ';
        if (isalpha(name.at(j)) && name.at(j-1) == ' ')
        name.at(j) = toupper(name.at(j));
    }
    if (isalpha(name.at(0)))
        	name.at(0) = toupper(name.at(0));

	//Final formating and function choose
	len = name.length();

	if (name.at(len-5) == '.' || slash == 3){	//Bulk download
        if (mode == 0){	//remove ".html" of long, bulk URL
            name = name.substr(0, name.find("."));
            nameorig = nameorig.substr(0, nameorig.find("."));
        }
        //Start Bulk
	cout << "\n\t" << "Name: " << name << endl;
	mangareaderbulk(url, name, nameorig, chapname, chapter, code, downdir, mode);
	}
  //Single chapter, long URL download
	else if (mode == 1){
        found = url.find("-", limit) + 1;
        limit = url.find(".", found);
        chapter = url.substr(found, limit - found);
        cout << "\n\t" << "Name: " << name << endl;
        cout << "\t" << "Chapter: " << chapter << endl;
        mangareadersingle(url, name, nameorig, chapter, downdir, mode);
	}
    //Single chapter, short URL download
    else if (mode == 0){
        chapter = url.substr(limit + 1);
        cout << "\n\t" << "Name: " << name << endl;
        cout << "\t" << "Chapter: " << chapter << endl;
        mangareadersingle(url, name, nameorig, chapter, downdir,mode);
    }
}

void mangareadersingle(string url, string name, string nameorig, string chapter, string downdir, bool mode){

	fstream fp;
	ofstream img;
curl_writer writer(fp);
curl::curl_easy curl(writer);
curl_writer draw(img);
curl::curl_easy pic(draw);

stringstream ss;
bool err = 0, result = 0, pgfound = 0;
short i=1, length;
string urldown, code, imgname, html, pageurl;
string tmpfile="/tmp/.html-mangareader-";
string baseurl	="http://www.mangareader.net/";
size_t found, limit;
	//to allow multiple instances of baamanga, one file per Manga
	tmpfile.append (name, 0, name.find(" "));

	//make directory
	namedir_check(name, downdir);
	downdir.append ("/" + name);
	chapdir_check(chapter, downdir);
	downdir.append ("/" + chapter);

    downdir_check(downdir);
	chdir(downdir.c_str());

    //urldown for long url system
    if(mode == 1){
        found = url.find ("/", 9) + 1;
        limit = url.find ("/", found);
        code = url.substr(found, limit - found - 1);
    }
    //urldown for short url system
    else if (mode == 0)
        code = "/" + nameorig + "/" + chapter + "/";

	while (err == 0){
		//restart "result" and "pgfound" values
		result		= 0;
		pgfound		= 0;

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
        fp.open(tmpfile, fstream::out);
        curl.add(curl_pair<CURLoption,string>(CURLOPT_URL, url));
		curl.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));

        try{
            curl.perform();
        } catch (curl_easy_exception error) {
                error.print_traceback();
        }
    fp.close();

    fp.open(tmpfile, fstream::in);
    while (getline(fp, html) && result == 0){
		if ((html.find (urldown) != string::npos) == 1){
            if (mode == 1){
                found = html.find(urldown);
                limit = html.find("\'", found);
                url = baseurl + (html.substr(found, limit - found));
            }


            else if (mode == 0){
                if (i > 1){
                    while(url.back() != '/'){
                        url.erase(url.find_last_of(url.back()));
                        length--;
                    }
                }
                else
                    url.append ("/" + ss.str());
            }
            result = 1;
	}
    }

	fp.seekg(0);

	if (result == 0)
		err = 1;

	while (getline(fp, html)){
		if ((html.find("http:") != string::npos) == 1 && (html.find(nameorig) != string::npos) == 1 && (html.find(".jpg") != string::npos) == 1){
			//cout << html << endl;
			found = html.find("http:");
			limit = html.find ("\"", found);
			pageurl = html.substr(found, limit - found);
			pgfound	= 1;
	    }
	}

	fp.close();

	if (pgfound == 1){
		cout << "\n\n\n";
		cout << "Downloading page " << i << "..." << endl;
		img.open(imgname);
		pic.add(curl_pair<CURLoption,string>(CURLOPT_URL, pageurl));
		pic.add(curl_pair<CURLoption,long>(CURLOPT_NOPROGRESS, 0L));
		pic.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION, 1L));

		try{
            pic.perform();
		}
		catch(curl_easy_exception error){
            error.print_traceback();
            }
        img.close();
		}

	i++;
	}

	if (i > 2)
		cout << "\n\n";
		cout << name << " chapter " << chapter << " downloaded." << endl;

	remove(tmpfile.c_str());

return;
}

void mangareaderbulk(string url, string name, string nameorig, string chapname, string chapter, string code, string downdir, bool mode){
    fstream bf;
curl_writer writer(bf);
curl::curl_easy blkcurl(writer);

stringstream ss;
short chapters=0, i=0, z=0;
string blkhtml, path2, path, downdir_orig;
string blktmpfile="/tmp/.baamanga-bulk-mangareader";
bool match=0;
char yesno;
size_t found, limit;

    //backup
    downdir_orig = downdir;

    //Default path 1
    path = nameorig + "/" + "1\""; // adding \" to avoid i.e. "chapter-13" as first coincidence
    //Default path 2
    path2 = nameorig + "/" + "chapter-1.html\""; // adding \" to avoid i.e. "chapter-13" as first coincidence
    //Download html
    bf.open(blktmpfile, fstream::out);
    blkcurl.add(curl_pair<CURLoption,string>(CURLOPT_URL,url));
    blkcurl.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));

    try{
        blkcurl.perform();
    }
    catch(curl_easy_exception error){
        error.print_traceback();
    }
    bf.close();
    //Count Chapters
    bf.open(blktmpfile, fstream::in);
    while (getline(bf, blkhtml)){
            //look for the path: style 1
            if ((blkhtml.find(path) != string::npos) == 1 && (blkhtml.find("chapter") != string::npos) == 0){
                path = nameorig + "/";
                //Default path 2
                path2 = nameorig + "/" + "chapter-";
                chapters++;
            }
            //Look for path style: 2
            else if ((blkhtml.find(path2) != string::npos) == 1 && (blkhtml.find(code) != string::npos) == 1){
                path = nameorig + "/";
                //Default path 2
                path2 = nameorig + "/" + "chapter-";

                chapters++;
            }
        }
    bf.close();

    //Ask for the first chapter to download for. Take 1 if not specified
    cout << "\n" << "There are " << chapters << " chapters, do you want to start downloading with some chapter in particular? [y/N] ";
		cin.get(yesno);

    if(yesno == 'y' || yesno == 'Y'){
        cout << "Which chapter do you want to start for? ";
        cin >> i;
    }
    else
        i=1;

    if (i > chapters){
        cout << "The chosed chapter does not exist, downloading from chapter 1" << endl;
        i = 1;
    }
    z = i;
    //Check if given chapter exists. Program takes next chapter in case the given one doesn't exist
    while(match==0){
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
        bf.open(blktmpfile, fstream::in);
        while (getline(bf, blkhtml)){
            if ((blkhtml.find(path) != string::npos) == 1 && (blkhtml.find("chapter") != string::npos) == 0){
                match=1;
            }
            if ((blkhtml.find(path2) != string::npos) == 1 && (blkhtml.find(code) != string::npos) == 1){
                match=1;
            }
        }
        bf.close();
        if (match==0){
            bf.seekg(0);
            i++;
        }
    }
    bf.seekg(0);

    if (z != i)
        cout << "Given chapter does not exist. Download will start from next available chapter (Chapter n. " << i << ")" << endl;

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

        match=0;

        bf.open(blktmpfile, fstream::in);
        while (getline(bf, blkhtml) && match == 0){
            if ((blkhtml.find(path) != string::npos) == 1 && (blkhtml.find("chapter") != string::npos) == 0){
                while(path.back() != '/'){
                    path.erase(path.find_last_of(path.back()));
                }
                while(path2.back() != '-'){
                    path2.erase(path2.find_last_of(path2.back()));
                }
                match=1;
            }
            if ((blkhtml.find(path2) != string::npos) == 1 && (blkhtml.find(code) != string::npos) == 1){
                while(path.back() != '/'){
                    path.erase(path.find_last_of(path.back()));
                }
                while(path2.back() != '-'){
                    path2.erase(path2.find_last_of(path2.back()));
                }
                match=1;
            }
        }
    }
    bf.close();

    //Download begins
    if(i > 1){
    path.append(ss.str());
    path2.append(ss.str() + ".html");;
    }

    bf.open(blktmpfile, fstream::in);
    while (getline(bf, blkhtml)){
        if ((blkhtml.find(path) != string::npos) == 1 && (blkhtml.find("chapter") != string::npos) == 0){
            mode = 0;
            found = blkhtml.find(path);
            limit = blkhtml.find("\"", found);
            url = "http://www.mangareader.net/" + blkhtml.substr(found, limit - found);
            chapter = url.substr(url.find_last_of("/") + 1);
            //chapter.erase(0);
            cout << "\n\t" << "Chapter: " << chapter << endl;
            mangareadersingle(url, name, nameorig, chapter, downdir, mode);
            while(path.back() != '/'){
                path.erase(path.find_last_of(path.back()));
            }
            while(path2.back() != '-'){
                path2.erase(path2.find_last_of(path2.back()));
            }
            downdir = downdir_orig;
		}

        if ((blkhtml.find(path2) != string::npos) == 1 && (blkhtml.find(code) != string::npos) == 1){
            mode = 1;
            found = blkhtml.find("\"") + 1;
            limit = blkhtml.find("\"", found);
            url = "http://www.mangareader.net" + blkhtml.substr(found, limit - found);
            found = url.find_last_of("-") + 1;
            limit = url.find(".", found);
            chapter = url.substr(found, limit - found);
            cout << "\n\t" << "Chapter: " << chapter << endl;
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
	remove(blktmpfile.c_str());
    cout << "\n\t" << "Download Finished" << endl;

return;
}
