#ifndef PERHAPS_SHADER
#define PERHAPS_SHADER
#include "../../PerhapsPch.h"

class Shader
{
public:
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc) : id(-1)
	{
		
	}

private:
	unsigned int id;
};

#endif