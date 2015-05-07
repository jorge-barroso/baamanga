#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <curlcpp/curl_easy.h>

using namespace std;

void submangasingle(string, string, string, string);
void submangabulk(string, string, string, string, string);
void namedir_check(string, string);
void chapdir_check(string, string);

void submanga(string url, string name, string downdir){
	short unsigned j;
	size_t found, limit;
	string discr, chapter, nameorig;

    found = url.find("/", 9) + 1;
	limit = url.find("/", found);
	name = url.substr(found, limit-found);
    nameorig = name;
	// Parse name
	for(j=0;j <= name.length() - 1 ; j++){
		if (name.at(j) == '_'){
			name.at(j) = ' ';
		}
	}
	found = limit + 1;
	limit = url.find("/", found);
	discr = url.substr(found, limit-found);

	if ((url.find("completa") != string::npos) == 1){
		submangabulk(url, name, nameorig, chapter, downdir);
		//cout << "Bulk function of submanga not yet available, sorry for the inconvenience" << endl;
	}
	else{
		chapter = discr;
		cout << "\n";
		cout << "\t" << "Name: " << name << endl;
		cout << "\t" << "Chapter: " << chapter << endl;
		submangasingle(url, name, chapter, downdir);
	}
  return;
}

void submangasingle(string url, string name, string chapter, string downdir){

	fstream fp;
	ofstream img;
curl_writer writer(fp);
curl::curl_easy curl(writer);
curl_writer draw(img);
curl::curl_easy pic(draw);

stringstream ss;
bool err = 0, pgfound = 0;
string urldown, pageurl, code;
string pgbaseone = "http://omg.submanga.com/pages";
string pgbasetwo = "http://img.submanga.com/pages";
string pgbasethree = "http://amg.submanga.com/pages";
string pgbasefour = "http://img2.submanga.com/pages";
string tmpfile = "/tmp/.html-submanga";
string imgname, html;
short result=0, i=1, k=0, mode = 0;
size_t found, limit;

	tmpfile.append (name, 0, 10);

	namedir_check	(name, downdir);
	downdir.append ("/" + name);
	chapdir_check	(chapter, downdir);
	downdir.append("/" + chapter);
	chdir		(downdir.c_str());

    code = url.substr(url.find_last_of("/") + 1);

	do{
		result = 0;
		pgfound = 0;
		ss << i;
		urldown = "http://submanga.com/c/" + code;
        if (i > 1)
            urldown.append("/" + ss.str());
        ss.str("");

        ss << k;
		if (k < 100)
            imgname = "0" + ss.str() + ".jpg";
        if (i < 10)
            imgname = "00" + ss.str() + ".jpg";
        ss.str("");

		/* Download html page*/
		fp.open(tmpfile, fstream::out);
		curl.add(curl_pair<CURLoption,string>(CURLOPT_URL, url));
		curl.add(curl_pair<CURLoption,long>(CURLOPT_FOLLOWLOCATION,1L));

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
		while (getline(fp, html)){
			if ((html.find(urldown) != string::npos) == 1){
                    url = urldown;
					result++;
				}
			}
        fp.close();

		if (result == 0)
			err = 1;

		/* HERE WE GET THE PAGE URL */

		if (i>1){
            fp.open(tmpfile, fstream::in);
			if (mode == 0){ //omg.submanga.com
				while (getline(fp, html)){
					if ((html.find(pgbaseone) != string::npos) == 1){
						found = html.find(pgbaseone);
						limit = html.find("\"", found);
						pageurl = html.substr(found, limit - found);
						pgfound = 1;
					}
				}
			}

			if (pgfound == 0 && i == 2){
				mode = 1;
				fp.seekg(0);
			}

			if (mode == 1){ //img.submanga.com
				while (getline(fp, html)){
					if ((html.find(pgbasetwo) != string::npos) == 1){
						found = html.find(pgbasetwo);
						limit = html.find("\"", found);
						pageurl = html.substr(found, limit - found);
						pgfound = 1;
					}
				}
			}

			if (pgfound == 0 && i == 2){
				mode = 2;
				fp.seekg(0);
			}

			if (mode == 2){ //amg.submanga.com
				while (getline(fp, html)){
					if ((html.find(pgbasethree) != string::npos) == 1){
						found = html.find(pgbasethree);
						limit = html.find("\"", found);
						pageurl = html.substr(found, limit - found);
						pgfound = 1;
					}
				}
			}

			if (pgfound == 0 && i == 2){
				mode = 3;
				fp.seekg(0);
			}

			if (mode == 3){ //img2.submanga.com
				while (getline(fp, html)){
					if ((html.find(pgbasefour) != string::npos) == 1){
						found = html.find(pgbasefour);
						limit = html.find("\"", found);
						pageurl = html.substr(found, limit - found);
						pgfound = 1;
					}
				}
			}
		}

		fp.close();
		if (i > 1 && pgfound == 1){
		/* Now for the image */
		img.open(imgname);

		cout << "\n\n";
		cout << "Downloading page " << k << "..." << endl;
		pic.add(curl_pair<CURLoption, string>(CURLOPT_URL, pageurl));
		pic.add(curl_pair<CURLoption, long>(CURLOPT_FOLLOWLOCATION,1L));
		pic.add(curl_pair<CURLoption, long>(CURLOPT_NOPROGRESS, 0L));

        try {
            pic.perform();
        }
        catch (curl_easy_exception error) {
            error.print_traceback();
        }

        img.close();
		}
		i++, k++;

	}while(err == 0);
	if (i > 2)
		cout << "\n\n";
		cout << name << " chapter " << chapter << " downloaded." << endl;
	remove(tmpfile.c_str());

return;
}

void submangabulk(string url, string name, string nameorig, string chapter, string downdir){
fstream bf;
curl_writer writer(bf);
curl::curl_easy curl (writer);

stringstream ss;
short chapters=0, i, j;
string blkhtml, newest;
string blktmpfile= "/tmp/.baamanga-bulk-submanga";
string urldown = "http://submanga.com/";
size_t found = 0, limit;

    urldown.append(nameorig + "/");

    bf.open(blktmpfile, fstream::out);
    curl.add(curl_pair<CURLoption, string>(CURLOPT_URL, url));
    curl.add(curl_pair<CURLoption, long>(CURLOPT_FOLLOWLOCATION, 1L));
    try{
        curl.perform();
    } catch (curl_easy_exception error){
            error.print_traceback();
        }
    bf.close();

    bf.open(blktmpfile, fstream::in);

    while(getline(bf, blkhtml)){
        while((blkhtml.find(urldown, found) != string::npos) == 1){
            found = blkhtml.find(urldown);
            limit = blkhtml.find("\"", found);
            cout << (blkhtml.substr(found, limit - found)) << endl;
            if ((blkhtml.substr(found, limit - found).find("completa") != string::npos) == 0)
                chapters++;
            if (chapters == 1){
                newest = blkhtml.substr(found, limit - found);
            found=limit + 1;
            }
        }
    }
    found = newest.find("/", 9) + 1;
    limit = newest.find("/", found);
    newest = newest.substr(found, limit - found);

    if(chapters < atoi(newest.c_str())){
        cout << "There are some missing chapters.";
        cout << "Latest chapter is " << newest << ", and there are " << chapters << " available chapters," << endl;
    }
    else
        cout << "There are " << chapters << " available  chapters." << endl;

    cout << "Which chapter do you want to start for? ";
    cin >> i;

    j = i;
return;
}
