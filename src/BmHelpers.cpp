//
// Created by jorge on 25/10/2019.
//

#include "BmHelpers.h"

void BmHelpers::displayHelp() {
    std::cout << "USAGE: baamanga [arguments] [url]" << std::endl;
    std::cout << "Both [arguments] and [url] are optional" << std::endl;
    std::cout << "Options are:" << std::endl;
    std::cout << "\t" << "config" << "\t\t\t\t" << "Show config dialog" << std::endl;
    std::cout << "\t" <<   "\n";
    std::cout << "\t" << "version" << "\t\t\t\t" << "Print version information and exit" << std::endl;
    std::cout << "\t" <<   "\n";
    std::cout << "\t" << "help" << "\t\t\t\t" << "Show this dialog" << std::endl;
}

void BmHelpers::config(const fs::path& confdir) {
    FileWriter conf;
    std::string dfolder;
    short formatnum {0};

    fs::current_path(confdir);
    conf.open("baamanga.conf");

    std::cout << "Where do you want your manga to be downloaded?: ";
    getline(std::cin, dfolder);
    if (dfolder.at(0) == '~' && dfolder.at(1) == '/'){
        dfolder.erase(0 , 2);
    }
    conf.write_line("downdir:"+dfolder);

    std::cout << "How do you want your downloaded manga?" << std::endl;
    do {
        std::cout << "\t" << "1. image" << std::endl << "\t" << "2. pdf" << std::endl << "\t" << "3. cbz" << "\n" << std::endl;
        std::cout << "\t" << "Introduce format number: ";
        std::cin >> formatnum;

        if(formatnum < 1 && formatnum > 3)
            std::cout << "Format number is incorrect, try again:" << std::endl;
        else
            break;
    }while (true);

    std::string format = "format:";
    switch(formatnum)
    {
        case 1:
            format += "image";
            break;
        case 2:
            format += "image";
            std::cout << "You have chosen pdf, which is not yet supported, manga format set as image." << std::endl;
            break;
        case 3:
            format += "image";
            std::cout << "You have chosen cbz, which is not yet supported, manga format set as image." << std::endl;
            break;
        default:
            break;
    }
    conf.write_line(format);
    conf.close();
}

void BmHelpers::displayVersion() {
    std::cout << "Baamanga version 1.0 (DATE)." << "\n" << std::endl;
    std::cout << "Copyright by Jorge Barroso <jorge_barroso_11 at hotmail dot com>." << std::endl;
    std::cout << "Distributed under GNU General Public License 2 (GPL 2.0)" << std::endl;
    std::cout << "Feel free to report any bug, issue or comment to https://github.com/jorge-barroso/baamanga" << std::endl;
}
