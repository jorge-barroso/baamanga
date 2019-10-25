#include "Properties.h"


Properties::Properties(const char * config_file)
{
	FileReader reader(config_file);
	std::string line;
	while (reader.read_line(line))
	{
		size_t split_token = line.find(properties_split);

		std::string key = line.substr(0, split_token);
		std::string value = line.substr(split_token + 1);
		Trimmer::trim(key);
		Trimmer::trim(value);

		properties_map.emplace(key, value);
	}
}


Properties::~Properties()
= default;


bool Properties::contains(std::string & key) const
{
	return !(this->properties_map.find(key) == this->properties_map.end());
}

void Properties::get(std::string & key, std::string & buff) const
{
	buff = this->properties_map.at(key);
}

std::string Properties::get(std::string & key) const
{
	return this->properties_map.at(key);
}

void Properties::get_or_default(std::string & key, std::string & default_value, std::string & buff) const
{
	buff = get_or_default(key, default_value);
}

std::string Properties::get_or_default(std::string & key, std::string & default_value) const
{
	if (this->contains(key))
		return this->get(key);
	else
		return default_value;
}

bool Properties::empty() const {
    return properties_map.empty();
}
