//
// Created by jorge on 25/10/2019.
//

#ifndef BAAMANGA_DIRSCHECKS_H
#define BAAMANGA_DIRSCHECKS_H

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

namespace fs = boost::filesystem;

class DirsChecks {
public:
    static void downdir_check(std::string& downdir);
    static void namedir_check(std::string &name, const  std::string &downdir);
    static void chapdir_check(std::string &chapter, const std::string &downdir);
    static void confdir_check(const fs::path& confdir);
private:
    static bool ok;
    //static struct stat d;
    //static int check;
    static char yesno;
    //static short int i;
};


#endif //BAAMANGA_DIRSCHECKS_H
