#include <iostream>
#include <string>
#include <unistd.h>
#include <ctype.h>
#include <curl/curl.h>

using namespace std;

void zerochansingle(string, string, string);
void zerochanbulk(string, string, string);

void zerochan(string url, string name, string downdir){
short unsigned int j;
bool discr;

	name = url.substr(url.find("/", 9) + 1);

	for(j=0;name.at(j)!='\0';j++){
		if (name.at(j) == '+' || isalpha(name.at(j)))
		discr = 1;
	}
	if (discr == 1){
		for(j=0;name.at(j)!='\0';j++){
			if (name.at(j) == '+' && name.at(j-1) != '\0'){
				name.at(j) = ' ';
				}
			}
		zerochanbulk(url, name, downdir);
	}
	else
		cout << "Please, give a name for the file you are going to download";
		getline(cin, name);
		 zerochansingle(url, name, downdir);
}

void zerochansingle(string url, string name, string downdir){
cout << "This is zerochansingle";
return;
}

void zerochanbulk(string url, string name, string downdir){

cout << "This is zerochanbulk";
return;
}
