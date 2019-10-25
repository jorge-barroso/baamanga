#pragma once
#include <string>
#include <iostream>
#include "FileManager.h"
class FileReader : FileManager
{
public:
	explicit FileReader(const std::string & filename);
	~FileReader();
	char read();
	std::string read_line();
	bool read_line(std::string & line);
	std::string read_all();
	void read_out();
	void rewind();
	void read_new(const std::string & filename);
	bool operator !();
private:
};

