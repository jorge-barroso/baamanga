#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <locale>
#include <curlcpp/curl_easy.h>
#include <unistd.h>

using namespace std;

void namedir_check(string, string);
void chapdir_check(string, string);
void mangafoxsingle(string, string, string, string, string);
void mangafoxbulk(string, string, string, string);

void mangafox(string url, string name, string downdir){
short unsigned l=0, slash=0;
string discr = "", chapter = "", chaptorig = "", nameorig = "";
size_t found, limit;
bool mode;

    for(l=0;l<url.length();l++){
        if (url.at(l) == '/')
            slash++;
    }

    if (slash < 6)
        mode=0;
    if (slash >= 6)
        mode=1;

    //Let's parse the name
    if (mode==0){
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

    for(l=1;l<name.length();l++){
        if (name.at(l) == '_')
            name.at(l) = ' ';
        if (isalpha(name.at(l)) && name.at(l-1) == ' '){
            name.at(l) = toupper(name.at(l));
        }
    }
    name.at(0) = toupper(name.at(0));
    if(mode == 0){
        cout << "\n\t" << "Name: " << name << endl;
		mangafoxbulk(name, nameorig, url, downdir);
	}
	else{
        //Now for the chapter
        found = limit + 1;
        limit = url.find ("/", found);
        discr = url.substr(found, limit - found);
		if (discr.at(0) != 'c'){
            found = limit + 1;
            limit = url.find ("/", found);
            chapter= url.substr(found, limit - found);    //it is a chapter, but this is the volume serial name
		}
		else
			chapter = discr;
			chaptorig = chapter;
		while (chapter.at(0) == 'c' || chapter.at(0) == '0')
			chapter.erase(chapter.begin());
		cout << "\n";
		cout << "\t" << "Name: " << name << endl;
		cout << "\t" << "Chapter: " << chapter << endl;
		mangafoxsingle(url, name, chapter, chaptorig, downdir);
	}
return;
}

void mangafoxsingle(string url, string name, string chapter, string chaptorig, string downdir){

	fstream fp;
	fstream img;
curl_writer writer(fp);
curl::curl_easy curl(writer);
curl_writer draw(img);
curl::curl_easy pic(draw);

stringstream ss;
short i=1, k=0;
size_t found, limit;
bool err=0, result=0, pgfound = 0;
string urldown;
string pgbase = "http://a.mfcdn.net/store/manga/";
string tmpfile = "/tmp/.html-mangafox";
string html, imgname, pageurl;

	tmpfile.append(name, 0, 10);

	namedir_check	(name, downdir);
	downdir.append ("/" + name);
	chapdir_check	(chapter, downdir);
	downdir.append ("/" + chapter);
	chdir		    (downdir.c_str());

	do{
		result = 0;
		pgfound = 0;
		ss << ++i;
            urldown = ss.str() + ".html";
        ss.str("");

        ss << ++k;
		if (k < 10)
            imgname = "00" + ss.str() + ".jpg";
        else if (i < 100)
            imgname = "0" + ss.str() + ".jpg";
        else
            imgname = ss.str() + ".jpg";
        ss.str("");
        i--, k--;

		/* Download html page*/
    fp.open(tmpfile, fstream::out);
	curl.add(curl_pair<CURLoption, string>(CURLOPT_URL, url));
	curl.add(curl_pair<CURLoption, long>(CURLOPT_FOLLOWLOCATION, 1L));

        try {
            curl.perform();
        }
        catch (curl_easy_exception error) {
            error.print_traceback();
        }
    fp.close();

	/* HERE STARTS HTML PARSING OF THE FILE */
	/* Look for the next html page to download */
	fp.open(tmpfile, fstream::in);
	while ( getline(fp, html) && result == 0){
		if ((html.find(urldown) != string::npos) == 1){
			url = url.substr(0, url.find_last_of("/") + 1) + urldown;
			result++;
		}
	}
	fp.seekg(0);

	/* HERE WE GET THE PAGE URL */
	while ( getline(fp, html) && pgfound == 0){
		if ((html.find(pgbase) != string::npos) == 1 && (html.find("compressed") != string::npos) == 1 && pgfound < 1) {
            found = html.find(pgbase);
            limit = html.find("\"", found);
            pageurl = html.substr(found, limit - found);
			pgfound++;
		}
	}

	fp.close();
	if (pgfound == 1){
		cout << "\n\n";
		cout << "Downloading page " << i << "..." << endl;
		img.open(imgname, fstream::out);

        pic.add(curl_pair<CURLoption,string>(CURLOPT_URL,pageurl));
        pic.add(curl_pair<CURLoption, long>(CURLOPT_NOPROGRESS, 0L));
        pic.add(curl_pair<CURLoption, long>(CURLOPT_FOLLOWLOCATION, 1L));

        try {
            pic.perform();
        }
        catch (curl_easy_exception error) {
            error.print_traceback();
        }
        img.close();
		}

	if (result == 0)
		err++;

    i++,k++;
	}while(err == 0);

	if (i > 2){
		cout << "\n" << endl;
		cout << name << " chapter " << chapter << " downloaded." << endl;
	}

return;
}

void mangafoxbulk(string name, string nameorig, string url, string downdir){
    fstream bf;
curl::curl_writer blkwriter(bf);
curl::curl_easy blkcurl(blkwriter);

stringstream ss;
string blkhtml, chapter;
string path="http://mangafox.me/manga/";
string blktmpfile="/tmp/.baamanga-bulk-mangafox";
short chapters=0, i, z;
char yesno;
bool match=0;
size_t found, limit;

    path.append (nameorig + "/");

    bf.open(blktmpfile, fstream::out);
    blkcurl.add(curl_pair<CURLoption,string>(CURLOPT_URL, url));
    blkcurl.add(curl_pair<CURLoption, long>(CURLOPT_FOLLOWLOCATION, 1L));

    try {
        blkcurl.perform();
    } catch (curl_easy_exception error) {
        error.print_traceback();
        }
    bf.close();

    bf.open(blktmpfile, fstream::in);
    while (getline(bf, blkhtml)){
            if ((blkhtml.find(path) != string::npos) == 1 && (blkhtml.find("1.html") != string::npos) == 1){
                chapters++;
            }
    }
    bf.close();

    //Ask for the first chapter to download for. Take 1 if not specified
    cout << "\n";
    cout << "There are " << chapters << " chapters, do you want to start downloading with some chapter in particular? [y/N] ";
    cin.get (yesno);

    if(yesno == 'y' || yesno == 'Y'){
        cout << "Which chapter do you want to start for? ";
        cin >> i;
    }
    else
        i=1;
    if (i > chapters)
        cout << "The chosed chapter does not exist, downloading from chapter 1" << endl;

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
        bf.open(blktmpfile, fstream::in);
        while (getline(bf, blkhtml) && match == 0){
            if((blkhtml.find(chapter) != string::npos) == 1)
                match=1;
        }
        bf.close();
        if (match == 0)
            ++i;
    }while(match==0);

    if (z != i)
        cout << "Given chapter does not exist. Download will start from next available chapter (Chapter n. " << i << endl;

    for (;i<=chapters;i++){
        ss << i;
        if (i < 10)
            chapter = "c00" + ss.str() + "/1.html";
        else if (i < 100)
            chapter = "c0" + ss.str() + "/1.html";
        else
            chapter = ss.str() + "/1.html";
        ss.str("");

        bf.open(blktmpfile, fstream::in);
        while(getline(bf, blkhtml)){
            if((blkhtml.find(chapter) != string::npos) == 1){
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
