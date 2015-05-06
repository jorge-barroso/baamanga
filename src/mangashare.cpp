#include <iostream>
#include <string>
#include <curl/curl.h>
#include <unistd.h>

using namespace std;

void mangashare(string url_orig, string name, string downdir){
short j;
string chapter;
size_t found, limit;

	//Name parse
	found = url_orig.find("/", 9) + 1;
	limit = url_orig.find("/", found);
	name = url_orig.substr(found, limit - found);
    for(j=0;name.at(j)!='\0';j++){
        if (name.at(j) == '-')
        name.at(j) = ' ';
    }
    //Parse chapter
    found = url_orig.find("-", limit) + 1;
    limit = url_orig.find ("/", found);
    chapter = url_orig.substr(found, limit - found);

cout << "\n\t" << "Name: " << name << endl;
cout << "\t" << "Chapter: "<< chapter << endl;
}
