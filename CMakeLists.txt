cmake_minimum_required(VERSION 3.15)
project(baamanga)
find_package(Boost)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -o2)

include_directories(include
        /usr/include/boost)

add_executable(baamanga
        src/Strings.cpp
        src/Baamanga.cpp
        src/DirsChecks.cpp
        src/downloads.cpp
        src/Strings.cpp
        src/Downloader.cpp
        src/BmHelpers.cpp
        src/Properties.cpp
        src/FileReader.cpp
        src/FileWriter.cpp)
