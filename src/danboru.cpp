#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <curlcpp/curl_easy.h>
#include <unistd.h>

using namespace std;

void danborudirect(string, string, string);
void danborusingle(string, string, string);
void danborubulk(string, string, string);

void danboru(string url, string name, string downdir){

    short slash=0, j;

    for (j=0;j < url.length();j++){
        if (url.at(j) == '/')
            slash++;
    }

	if ((url.find("posts") != string::npos) == 1){
		if (slash == 3)
            danborubulk(url, name, downdir);
        else
            danborusingle(url, name, downdir);
		}
	else if ((url.find("data") != string::npos) == 1)
        danborudirect(url, name, downdir);



return;
}


void danborudirect(string url, string name, string downdir){
    ofstream dp;
curl_writer dwriter(dp);
curl::curl_easy dcurl(dwriter);

    if (name.empty()){
        cout << "Select a name for your downloaded file: ";
        getline (cin, name);
    }

    chdir(downdir.c_str());

	dp.open(name);
		dcurl.add(curl_pair<CURLoption,string>(CURLOPT_URL, url));
        dcurl.add(curl_pair<CURLoption, long>(CURLOPT_NOPROGRESS, 0L));
		dcurl.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));

    try {
        dcurl.perform();
    } catch (curl_easy_exception error) {
        error.print_traceback();
    }

	dp.close();
return;
}

void danborusingle(string url, string name, string downdir){
    fstream fp;
    ofstream img;
curl_writer writer(fp);
curl::curl_easy curl(writer);
curl_writer draw(img);
curl::curl_easy pic(draw);

string urldown = "http://danbooru.donmai.us/data/";
string tmpfile = "/tmp/.html-danbooru";
string html, boardurl;
size_t found, limit;

    chdir(downdir.c_str());

    fp.open(tmpfile, fstream::out);
    curl.add(curl_pair<CURLoption, string>(CURLOPT_URL, url));
    curl.add(curl_pair<CURLoption, long>(CURLOPT_FOLLOWLOCATION, 1L));

    try{
        curl.perform();
    } catch (curl_easy_exception error){
            error.print_traceback();
        }
    fp.close();

    if (name.empty()){
        cout << "Give a name to the board: ";
        getline (cin, name);
    }

    fp.open(tmpfile, fstream::in);
    while(getline(fp, html)){
        if ((html.find(urldown) != string::npos) == 1){
            found = html.find(urldown);
            limit = html.find ("\"", found);
            boardurl = html.substr(found, limit - found);
        }
    }
    fp.close();

        img.open(name);
        pic.add(curl_pair<CURLoption, string>(CURLOPT_URL, boardurl));
        pic.add(curl_pair<CURLoption, long>(CURLOPT_NOPROGRESS, 0L));
        pic.add(curl_pair<CURLoption, long>(CURLOPT_FOLLOWLOCATION, 1L));

        try {
            pic.perform();
        } catch(curl_easy_exception error){
                error.print_traceback();
        }
        img.close();

        cout << "*******************************************";
        cout << "*******************************************" << endl;
        cout << "Download of " << name << " finished" << endl;

return;
}

void danborubulk(string url, string name, string downdir){
    fstream fp;
curl_writer writer(fp);
curl::curl_easy curl(writer);

stringstream ss;
string blktmpfile = "/tmp/.baamanga-bulk-danbooru";
string blkurldown = "data-large-file-url";
string page, blkhtml;
short i=1, j=2;
bool pgfound, err=0;
size_t found, limit;
    //do{
        fp.open(blktmpfile, fstream::out);
        curl.add(curl_pair<CURLoption, string>(CURLOPT_URL, url));
        curl.add(curl_pair<CURLoption, long>(CURLOPT_FOLLOWLOCATION, 1L));

        try{
            curl.perform();
        } catch (curl_easy_exception error){
                error.print_traceback();
            }
        fp.close();
        /*ss << j;
        page = "http://danbooru.donmai.us/posts?page=" + ss.str();
        ss.str("");*/
        fp.open(blktmpfile, fstream::in);
        while(getline(fp, blkhtml)){
            if ((blkhtml.find(blkurldown) != string::npos) == 1){
                found = blkhtml.find("\"") + 1;
                limit = blkhtml.find ("\"", found);
                url = "http://danbooru.donmai.us" + blkhtml.substr(found, limit - found);
                ss << i;
                name = ss.str();
                cout << "\n\n" << "Downloading board n." << name << "..." << endl;
                danborudirect(url, name, downdir);
                i++;
                ss.str("");
            }
            /*if ((blkhtml.find(page) != string::npos) == 1){
                cout << page << endl;
                found = blkhtml.find(page);
                limit = blkhtml.find ("\"", found);
                url = blkhtml.substr(found, limit - found);
                cout << url << endl;
                pgfound = 1;
            }
            else
                err = 0;*/
        }
        fp.close();
        /*if (pgfound == 0)
            err = 1;
        else
            j++;
    }while (err==0);*/

    remove (blktmpfile.c_str());
return;
}
