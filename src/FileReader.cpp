#include "FileReader.h"


FileReader::FileReader(const std::string & filename):FileManager()
{
	file.open(filename, std::ios_base::in);
}


FileReader::~FileReader()= default;

char FileReader::read()
{
	if (file.eof())
		return 0;

	return file.get();
}

std::string FileReader::read_line()
{
	if (file.eof())
		return "";

	std::string line;
	std::getline(file, line);

	return line;
}

bool FileReader::read_line(std::string & line)
{
	if (file.eof())
		return false;
	std::getline(file, line);

	return true;
}

std::string FileReader::read_all()
{
	std::string contents;
	std::string line;
	while (!(line = read_line()).empty())
	{
		contents += line;
	}

	rewind();
	return contents;
}

void FileReader::read_out()
{
	std::string line;
	while (this->read_line(line))
	{
		std::cout << line << std::endl;
	}

	rewind();
}

void FileReader::rewind()
{
	file.clear();
	file.seekg(0, std::ios::beg);
}

void FileReader::read_new(const std::string & filename)
{
	this->open_new(file, filename, std::ios_base::in);
}

bool FileReader::operator!()
{
	return !file;
}
