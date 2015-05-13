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
			if (mode == 0){ //omg.submanga.com
                fp.open(tmpfile, fstream::in);
				while (getline(fp, html)){
					if ((html.find(pgbaseone) != string::npos) == 1){
						found = html.find(pgbaseone);
						limit = html.find("\"", found);
						pageurl = html.substr(found, limit - found);
						pgfound = 1;
					}
				}
                fp.close();
			}

			if (pgfound == 0 && i == 2)
				mode = 1;

			if (mode == 1){ //img.submanga.com
                fp.open(tmpfile, fstream::in);
				while (getline(fp, html)){
					if ((html.find(pgbasetwo) != string::npos) == 1){
						found = html.find(pgbasetwo);
						limit = html.find("\"", found);
						pageurl = html.substr(found, limit - found);
						pgfound = 1;
					}
				}
                fp.close();
			}

			if (pgfound == 0 && i == 2)
				mode = 2;

			if (mode == 2){ //amg.submanga.com
                fp.open(tmpfile, fstream::in);
				while (getline(fp, html)){
					if ((html.find(pgbasethree) != string::npos) == 1){
						found = html.find(pgbasethree);
						limit = html.find("\"", found);
						pageurl = html.substr(found, limit - found);
						pgfound = 1;
					}
				}
                fp.close();
			}

			if (pgfound == 0 && i == 2)
				mode = 3;

			if (mode == 3){ //img2.submanga.com
                fp.open(tmpfile, fstream::in);
				while (getline(fp, html)){
					if ((html.find(pgbasefour) != string::npos) == 1){
						found = html.find(pgbasefour);
						limit = html.find("\"", found);
						pageurl = html.substr(found, limit - found);
						pgfound = 1;
					}
				}
            fp.close();
			}
		}

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
fstream spec;
curl_writer writer(bf);
curl::curl_easy curl (writer);

stringstream ss;
short chapters=0, spchapters = 0, i, j;
string blkhtml, newest;
string blktmpfile= "/tmp/.baamanga-bulk-submanga";
string urldown = "http://submanga.com/";
size_t found, limit, foundspec = -1;
char spask;
bool check = 0, match = 0;

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
    spec.open("/tmp/.special_chapters", fstream::out);
    while(getline(bf, blkhtml)){
            found = 0;
        while((blkhtml.find(urldown, found) != string::npos) == 1){

            //delimit the found url
            found = blkhtml.find(urldown,found);
            limit = blkhtml.find("\"", found);

            //find the beggining of special chapters
            if ((blkhtml.find("Especiales") != string::npos) == 1)
                foundspec = blkhtml.find("Especiales");

            //check if is a regular or a special chapter
            if ((blkhtml.substr(found, limit - found).find("completa") != string::npos) == 0 && (blkhtml.substr(found, limit - found).find("scanlations") != string::npos) == 0 && (foundspec == -1 || found < foundspec))
                chapters++;
            else if (foundspec != -1 && found > foundspec){
                spchapters++;
                spec << blkhtml.substr(found, limit - found) << endl;
            }

            //check if there is chapter 0
            if ((blkhtml.substr(found, limit - found).find("/0/") != string::npos) == 1)
                check=1;

            //get newest chapter url, to get the higher chapter available
            if (chapters == 1)
                newest = blkhtml.substr(found, limit - found);

            //update found to continue looking for coincidences
            found=limit + 1;
            }
    }
    spec.close();
    bf.close();
    //get the latest chapter number
    found = newest.find("/", newest.find("/", 9) + 1) +1;
    limit = newest.find("/", found);
    newest = newest.substr(found, limit - found);

    //check whether it is complete and inform if it's not
    if(chapters < atoi(newest.c_str())){
        cout << "\n" << "There are some missing chapters. ";
        cout << "Latest chapter is " << newest << ", but there are " << chapters << " available chapters." << endl;
    }
    else
        cout << "There are " << chapters << " available chapters. ";

    //inform if there is a Chapter 0
    if (check == 1)
         cout << "A \"Chapter 0\" was found." << "\n" << endl;
    else
        cout << "\n" << endl;

    //inform of special chapters and ask to download them
    if (spchapters > 0){
        do{
            cout << "\n" << spchapters << " special chapters were found, do you want to download them? [Y/n/v(view)] ";
            cin.get(spask);
            cin.clear(); cin.ignore(INT_MAX,'\n');
            if (spask == 'v' || spask == 'v'){
                spec.open("/tmp/.special_chapters", fstream::in);
                while (getline(spec, blkhtml))
                    cout << blkhtml << endl;
                spec.close();
            }
        }while (spask != 'y' && spask != 'Y' && spask != 'n' && spask != 'N');
        cout << "\n" << "Ok, now let's start downloading the regular chapters. ";
    }

    cout << "Which chapter do you want to start for? ";
    cin >> i;
    j = i;

    if (i > atoi(newest.c_str())){
        cout << "Introduced chapter is higher than the biggest chapter of that manga, the download will start by the first available chapter (chapter n. ";
        if (check == 1)
            i = 0;
        else if (check == 0)
            i = 1;
        cout << i << ")"<< endl;
        }
//check if chosen chapter exists
do{
    ss << i;
    urldown.append(ss.str() + "/");
    ss.str("");
    bf.open(blktmpfile, fstream::in);
    while (getline(bf, blkhtml))
        if ((blkhtml.find(urldown) != string::npos) == 1)
            match = 1;
    bf.close();

    do{
        urldown.erase(urldown.find_last_of(urldown.back()));
    }while(urldown.back() != '/');

    if (match==0)
        i++;
}while (match == 0);

//If chosen chapter is not available, inform which chapter will be downloaded (the next available)
if(j!=i)
    cout << "Chapter " << j << "is not available, next available chapter will be downloaded (" << i << ")." << endl;

//Start download
for (;i<=atoi(newest.c_str());i++){
    ss << i;
    urldown.append(ss.str() + "/");
    ss.str("");
    bf.open(blktmpfile, fstream::in);
    while (getline(bf, blkhtml)){
        if ((blkhtml.find(urldown) != string::npos) == 1){
            found = blkhtml.find(urldown);
            limit = blkhtml.find("\"", found);
            url = blkhtml.substr(found, limit - found);
            submanga(url, name, downdir);
        }
    }
    bf.close();
    do{
        urldown.erase(urldown.find_last_of(urldown.back()));
    }while(urldown.back() != '/');
}

if (spask != 'n' && spask != 'N' && spask != 'v' && spask != 'V'){
    cout << "\n" << "DOWNLOADING SPECIAL CHAPTERS:" << endl;
    spec.open("/tmp/.special_chapters", fstream::in);
    while(getline(spec, blkhtml)){
        url = blkhtml;
        submanga(url, name, downdir);
    }
}

cout << "Every chapter has been successfully downloaded. Be back soon!" << endl;

return;
}
