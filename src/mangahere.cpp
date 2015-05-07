#include <iostream>
#include <string>
#include <unistd.h>
#include <ctype.h>

using namespace std;

void mangaheresingle(string, string, string, string);
void mangaherebulk(string, string, string, string);

void mangahere(string url, string name, string downdir){
	int j;
    string chapter;
    size_t found, limit;

    found = url.find("/", 9) + 1;
	found = url.find("/", found) + 1;
	limit = url.find("/", found);
	// Parse name
	name = url.substr(found, limit - found);

	for(j=0;name.at(j)!='\0'; j++){
		if (name.at(j) == '_'){
			name.at(j) = ' ';
		}
		if (isalpha(name.at(j)) && name.at(j-1) == ' ')
			name.at(j) = toupper(name.at(j));
	}
	if (isalpha(name.at(0)))
		name.at(0) = toupper(name.at(0));

    found = limit + 1;
    limit = url.find("/", found);
	chapter = url.substr(found, limit - found);

	if (chapter.compare("http:") == 0)
		mangaherebulk(url, name, chapter, downdir);
	else{
		chapter = url.substr(limit +1);
        chapter.back() = '\0';
		mangaheresingle(url, name, chapter, downdir);
	}
		cout << "\t" << "Name: " << name << endl;
		cout << "\t" << "Chapter: " << chapter << endl;
return;
}


void mangaheresingle(string url, string name, string chapter, string downdir){
cout << "This is mangaheresingle";
return;
}

void mangaherebulk(string url, string name, string chapter, string downdir){
cout << "This is mangaherebulk";
return;
}
