#include <iostream>
#include <string>
#include <curl/curl.h>
#include <unistd.h>

using namespace std;

void mangashare(string url, string name, string downdir){
short j;
string chapter;
size_t found, limit;

	//Name parse
	found = url.find("/", 9) + 1;
	limit = url.find("/", found);
	name = url.substr(found, limit - found);
    for(j=0;name.at(j)!='\0';j++){
        if (name.at(j) == '-')
        name.at(j) = ' ';
    }
    //Parse chapter
    found = url.find("-", limit) + 1;
    limit = url.find ("/", found);
    chapter = url.substr(found, limit - found);

cout << "\n\t" << "Name: " << name << endl;
cout << "\t" << "Chapter: "<< chapter << endl;
}
