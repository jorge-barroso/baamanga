#pragma once
#include "FileReader.h"
#include "Trimmer.h"
#include <unordered_map>
class Properties
{
public:
	explicit Properties(const char * config_file);
	~Properties();
	bool contains(std::string & key) const;
	void get(std::string & key, std::string & buff)  const;
	std::string get(std::string & key) const;
	void get_or_default(std::string & key, std::string & default_value, std::string & buff) const;
	std::string get_or_default(std::string & key, std::string & default_value) const;
	bool empty() const;
protected:
	char properties_split = ':';
	std::unordered_map<std::string, std::string> properties_map;
};

