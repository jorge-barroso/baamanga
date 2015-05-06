#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

using namespace std;

void confdir_check(string);

void config(string confdir){
    ofstream conf;
	string dfolder;
	short formatnum;

	chdir(confdir.c_str());

	cout << "Where do you want your manga to be downloaded?: ";
	getline(cin, dfolder);
    if (dfolder.at(0) == '~'){
        string home = getenv("HOME");
        dfolder.replace(0,1, home);
    }

	cout << "How do you want your downloaded manga?" << endl;
	cout << "\t" << "1. image" << endl << "\t" << "2. pdf" << endl << "\t" << "3. cbz" << "\n" << endl;
	cout << "\t" << "Introduce format number: ";
	cin >> formatnum;

    while (formatnum != 1 && formatnum != 2 && formatnum != 3){
	cout << "Format number is incorrect, try again:" << endl;
	cout << "\t" << "1. image" << endl << "\t" << "2. pdf" << endl << "\t" << "3. cbz" << "\n" << endl;
	cout << "\t" << "Introduce format number: ";
	cin >> formatnum;
	}

    conf.open("baamanga.conf");
    conf << "Downdir=" + dfolder + "\n";
	if(formatnum==1)
		conf << "Format=image";
	else if (formatnum==2){
		conf << "Format=image";
		cout << "You have chosen pdf, which is not yet supported, manga format set as image." << endl;
	}
	else if (formatnum==3){
		conf << "Format=image";
		cout << "You have chosen cbz, which is not yet supported, manga format set as image." << endl;
	}
	conf.close();
return;
}
