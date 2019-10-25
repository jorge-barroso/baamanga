#pragma once
#include "FileManager.h"
class FileWriter :
	public FileManager
{
public:
	FileWriter();
	explicit FileWriter(const char *filename, bool append = false);
	~FileWriter();
	template<typename T>
	void write_line(T val);
	void open(const std::string & filename);
	void close();
private:
	const std::ios_base::openmode mode;
};

template<typename T>
inline void FileWriter::write_line(T val)
{
	file << val << " " << std::endl;
}
