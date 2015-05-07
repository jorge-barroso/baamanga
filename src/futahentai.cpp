#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

void futahentai(string url, string name, string downdir){
short j, found, limit;
string chapter;

    //Let's parse the name
	found = url.find("-") + 1;
	limit = url.find("-", found);
	name = url.substr(found, limit - found - 1);
	for(j=0;name.at(j)!='\0';j++){
		if (name.at(j) == '_')
			name.at(j) = ' ';
}
	//Parsing chapter
	found = limit + 1;
	limit = url.find(".", found);
	chapter = url.substr(found, limit - found - 1);

    cout << "\n";
	cout << "\t" << "Name: " << name << endl;
	cout << "\t" << "Chapter: " << chapter << endl;

return;
}
