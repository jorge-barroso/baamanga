#pragma once
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
/*https://stackoverflow.com/a/217605/4761359
 this methods use find_if to find a character that is not a space and delete up until there/from there
*/
class Trimmer
{
public:
	// trim from start (in place)
	static inline void left_trim(std::string &s);

	// trim from end (in place)
	static inline void right_trim(std::string &s);

	// trim from both ends (in place)
	static inline void trim(std::string &s);
};

inline void Trimmer::left_trim(std::string & s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

inline void Trimmer::right_trim(std::string & s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

inline void Trimmer::trim(std::string & s)
{
	left_trim(s);
	right_trim(s);
}