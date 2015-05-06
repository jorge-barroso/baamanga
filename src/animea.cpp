#include <iostream>
#include <string>
//#include <curl/curl.h>
//#include <ctype.h>

using namespace std;

void animeasingle(string, string, string, string, string);
void animeabulk(string, string, string, string);



void animea(string url_orig, string name, string downdir){
string discr, chapter;
short found;

    found = url_orig.find_last_of("/");
	discr = url_orig.substr(found + 1);

	if((discr.find("chapter") != string::npos) == 1){
		animeasingle(url_orig, name, chapter, discr, downdir);
	}
	else{
		animeabulk(url_orig, name, chapter, downdir);
	}
return;
}

void animeasingle(string url_orig, string name, string chapter, string discr, string downdir){
	string namex;
	short unsigned int j;
	size_t found, limit;

    //Complex name parsing
		name = discr.substr(0, discr.find("-chapter-"));

    //Now starts capitalizing
	for (j=0; name.at(j)!='\0'; j++){
		if (isalpha(name.at(j)) && name.at(j-1) == ' ')
			name.at(j) = toupper(name.at(j));
		}
	if (isalpha(name.at(0)))
		name.at(0) = toupper(name.at(0));

	//Chapter
	found = url_orig.find_last_of("-") + 1;
    limit = url_orig.find_last_of(".", found);
    discr = url_orig.substr(found, limit - found -1);
	chapter = url_orig.substr(found, limit - found -1);

	cout << "\t" << "Name: " << name << endl;
	cout << "\t" << "Chapter: " << chapter << endl;
return;
}

void animeabulk(string url_orig, string name, string chapter, string downdir){
return;
}
