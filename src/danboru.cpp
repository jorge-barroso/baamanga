#include <iostream>
#include <string>
#include <fstream>
#include <curlcpp/curl_easy.h>
#include <unistd.h>

using namespace std;

void danborudirect(string, string, string);
void danborusingle(string, string, string);
void danborubulk(string, string, string, string);

void danboru(string url_orig, string name, string downdir){

	string chapter;
    size_t match;


    match = url_orig.find("/", url_orig.find("/") + 1); //find last "/" oh "http://"
    name = url_orig.substr(url_orig.find("/", match + 1) +1, url_orig.find("-chapter-")-url_orig.find("/", match + 1) -1);
           /*call substr    //start on next "/" +1 (after domain)    //length == position of first "-chapter-" char - beggining -1
                                                                                (end - beggining == length between both)*/
	if (name.compare("posts") == 0){
	name = url_orig.substr(url_orig.find_last_of("/")+1);
		if (isalpha(name.at(1)))
				danborubulk(url_orig, name, chapter, downdir);
			else{
				danborusingle(url_orig, name, downdir);
			}
		}
	else if (name.compare("data") == 0){
	danborudirect(url_orig, name, downdir);
	}



return;
}


void danborudirect(string url_orig, string name, string downdir){
    ofstream fp;
curl_writer writer(fp);
curl::curl_easy curl(writer);

    cout << "Select a name for your downloaded file: ";
    getline (cin, name);

    chdir(downdir.c_str());
	fp.open(name);

		curl.add(curl_pair<CURLoption,string>(CURLOPT_URL, url_orig));
		curl.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));

    try {
        curl.perform();
    } catch (curl_easy_exception error) {
        error.print_traceback();
    }

	fp.close();
return;
}

void danborusingle(string url_orig, string name, string downdir){
return;
}

void danborubulk(string url_orig, string name, string chapter, string downdir){

cout << "This is danborubulk";
//Name
cout << "Give a name to the board: ";
getline (cin, name);
return;
}
