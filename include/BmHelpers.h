//
// Created by jorge on 25/10/2019.
//

#ifndef BAAMANGA_BMHELPERS_H
#define BAAMANGA_BMHELPERS_H

#include <iostream>
#include <string>
#include <fstream>
#include "FileWriter.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
namespace fs = boost::filesystem;
class BmHelpers {
    public:
        static void displayHelp();
        static void config(const fs::path& confdir);
        static void displayVersion();
};


#endif //BAAMANGA_BMHELPERS_H
