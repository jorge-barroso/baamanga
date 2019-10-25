#include <DirsChecks.h>

bool DirsChecks::ok = false;
char DirsChecks::yesno;

void DirsChecks::downdir_check(std::string &downdir){
    do{
        if(!fs::exists(downdir)){
            fs::create_directory(downdir);
            ok = true;
        }
        else if (!fs::is_directory(downdir)){
		std::cout << "A file with the download directory already exists." << std::endl;
		std::cout << "Do you want to overwrite with a directory? [y/N]" << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cin.get (yesno);

			if (yesno == 'y' || yesno == 'Y'){
				fs::remove (downdir);
				fs::create_directory(downdir);
				ok = true;
			}
			else{
				std::cout << "Choose a new path to download your manga." << std::endl;
				std::cout << "(full path): ";
				getline (std::cin, downdir);
				ok = false;
				}
			}
        else ok = true;
	}while (!ok);
}

void DirsChecks::namedir_check(std::string &name, const std::string &downdir){

	fs::current_path(downdir);
	ok=false;
	while (!ok){

        if(!fs::exists(name))
            fs::create_directory(name);

        else if (!fs::is_directory(name)){
            std::cout << "A file with the name of your manga already exists." << std::endl;
            std::cout << "Do you want to overwrite it? [y/N]" << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;
            std::cin.get(yesno);
            if (yesno == 'y'){
                fs::remove (name);
                fs::create_directory(name);
                ok = true;
            }
            else{
                std::cout << "Choose a new directory to download " << name << "." << std::endl;
                getline (std::cin, name);
            }
        }
        else ok = true;
	}
}

void DirsChecks::chapdir_check(std::string &chapter, const std::string &downdir){

	fs::current_path(downdir);
	ok=false;
	while (!ok){

	    if(!fs::exists(chapter))
        {
            fs::create_directory(chapter);
        }
	    else if (!fs::is_directory(chapter))
        {
            std::cout << "A file with the chapter of your manga already exists.\nDo you want to overwrite it? [y/N]" << std::endl;
            ///std::cout << "(Use \"\" if space): ";
            std::cout << "-----------------------------------------------" << std::endl;
            std::cin.get (yesno);
            if (yesno== 'y')
            {
                fs::remove (chapter);
                fs::create_directory(chapter);
                ok = true;
            }
            else
            {
                std::cout << "Choose a new directory to download the chapter." << std::endl;
                ///std::cout << "(Use \"\" if space): ";
                getline (std::cin, chapter);
            }
        }
	    else ok = true;
	}
}

void DirsChecks::confdir_check(const fs::path& confdir){
    fs::path confdirbackup=".config/baamanga.backup";

    if(!fs::exists(confdir))
    {
        fs::create_directory(confdir);
    }
    else if (!fs::is_directory(confdir))
	{
		std::cout << "A file with the download directory name already exists." << std::endl;
		std::cout << "Saved as " << confdir << ".backup, making config directory." << std::endl;
        fs::rename (confdir, confdirbackup);
        fs::remove (confdir);
        fs::create_directory(confdir);
    }
    else ok = true;
}
