#include "FileWriter.h"


FileWriter::FileWriter() : mode { std::ios_base::out | std::ios_base::app  }
{}

FileWriter::FileWriter(const char *filename, bool append)
	: mode{ append ? std::ios_base::out | std::ios_base::app  : std::ios_base::out}
{
	file.open(filename, mode);
}

FileWriter::~FileWriter()
{
	file.close();
}

void FileWriter::open(const std::string & filename)
{
	this->open_new(file, filename, mode);
}

void FileWriter::close()
{
	file.flush();
	file.close();
}
