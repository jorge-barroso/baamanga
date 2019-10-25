//
// Created by jorge on 25/10/2019.
//

#ifndef BAAMANGA_DOWNLOADER_H
#define BAAMANGA_DOWNLOADER_H

#include <string>

class Downloader {
    virtual bool getNextChapter() = 0;
    virtual void download() = 0;
};


#endif //BAAMANGA_DOWNLOADER_H
