#pragma once
#include <string>
#include <fstream>
#include "ExceptionConstants.h"
class FileManager
{
protected:
	template <class Stream>
	void open_new(Stream& stream, std::string newFile, std::ios_base::openmode mode);
	std::fstream file;
};

////https://stackoverflow.com/questions/2284775/c-can-i-reuse-fstream-to-open-and-write-multiple-files
template<class Stream>
inline void FileManager::open_new(Stream & stream, const std::string newFile, const std::ios_base::openmode mode)
{
	stream.close();
	stream.clear();
	stream.open(newFile, mode);

	if (!stream)
		throw ExceptionConstants::FILE_NOT_FOUND;
}
