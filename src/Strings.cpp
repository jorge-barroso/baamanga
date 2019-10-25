#include <string>

unsigned long counter;

void capitalize(std::string &value)
{
    for (counter=1; counter<value.length(); counter++){
            if (isalpha(value.at(counter)) && value.at(counter-1) == ' ')
                value.at(counter) = toupper(value.at(counter));
        }
        if (isalpha(value.at(0)))
            value.at(0) = toupper(value.at(0));
}

void  normalize(std::string &value)
{
    for(counter=0; counter <= value.length() - 1 ; counter++){
		if (value.at(counter) == '_' || value.at(counter) == '-'){
            value.at(counter) = ' ';
		}
	}
}
void repair(std::string &value)
{
    normalize(value);
    capitalize(value);
}
