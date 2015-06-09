#include <string>

unsigned short counter;

std::string capitalize(std::string arg)
{
    for (counter=1; counter<arg.length(); counter++){
            if (isalpha(arg.at(counter)) && arg.at(counter-1) == ' ')
                arg.at(counter) = toupper(arg.at(counter));
        }
        if (isalpha(arg.at(0)))
            arg.at(0) = toupper(arg.at(0));

return arg;
}

std::string normalize(std::string arg)
{
    for(counter=0;counter <= arg.length() - 1 ; counter++){
		if (arg.at(counter) == '_' || arg.at(counter) == '-'){
			arg.at(counter) = ' ';
		}
	}

return arg;
}
std::string repair(std::string arg)
{
    arg = normalize(arg);
    arg = capitalize(arg);

return arg;
}
