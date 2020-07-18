#ifndef PERHAPS_UTILS
#define PERHAPS_UTILS
#include "../../PerhapsPch.h"

class PerhapsUtils
{
	public:
	static std::vector<std::string> SubString(std::string source, const std::string& delimiter)
	{
		size_t pos = 0;

		std::string token;
		std::vector<std::string> entries;

		while ((pos = source.find(delimiter)) != std::string::npos) {
			token = source.substr(0, pos);
			std::cout << token << std::endl;
			source.erase(0, pos + delimiter.length());
			entries.push_back(token);
		}

		return entries;
	}

};

#endif