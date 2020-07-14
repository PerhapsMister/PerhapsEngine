#ifndef PERHAPS_SHADER
#define PERHAPS_SHADER
#include "../../PerhapsPch.h"

class Shader
{
public:

	static Shader* CompileShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		unsigned int vertID = CompileSource(vertexSrc, ShaderType::VERTEX);
		unsigned int fragID = CompileSource(fragmentSrc, ShaderType::FRAGMENT);

		unsigned int programId = glCreateProgram();
		glAttachShader(programId, vertID);
		glAttachShader(programId, fragID);
		glLinkProgram(programId);

		glDeleteShader(vertID);
		glDeleteShader(fragID);

		int succ;
		glGetProgramiv(programId, GL_LINK_STATUS, &succ);
		if (!succ)
		{
			char info[512];
			glGetProgramInfoLog(programId, 512, NULL, info);
			conlog("Shader program linking error: " << info);
			return nullptr;
		}

		Shader* shader = new Shader();
		shader->programId = programId;
		return shader;
	}

	void Bind()
	{
		if (programId != -1)
		{
			glUseProgram(programId);
			bound = this;
		}
	}

	bool IsBound()
	{
		return bound == this;
	}

	static void Unbind()
	{
		glUseProgram(0);
		bound = nullptr;
	}

private:
	static Shader* bound;

	Shader() : programId(-1)
	{

	}


	enum class ShaderType
	{
		VERTEX = GL_VERTEX_SHADER, FRAGMENT = GL_FRAGMENT_SHADER
	};

	static unsigned int CompileSource(const std::string& shaderSrc, ShaderType type)
	{
		unsigned int shaderId;
		shaderId = glCreateShader((GLenum)type);
		const char* src = shaderSrc.c_str();

		glShaderSource(shaderId, 1, &src, NULL);
		glCompileShader(shaderId);
		

		int succ;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &succ);
		if (!succ)
		{
			char info[512];
			glGetShaderInfoLog(shaderId, 512, NULL, info);
			conlog("Shader compilation error: " << info);
			return -1;
		}

		return shaderId;
	}

	unsigned int programId;
};

Shader* Shader::bound = nullptr;
PAPI void Shader_Bind(Shader* shader)
{
	shader->Bind();
}

PAPI void Shader_Unbind()
{
	Shader::Unbind();
}

PAPI bool Shader_IsBound(Shader* shader)
{
	return shader->IsBound();
}

PAPI Shader* Shader_CompileShader(const char* vertSrc, const char* fragSrc)
{
	return Shader::CompileShader(vertSrc, fragSrc);
}

PAPI void Shader_Delete(Shader* shader)
{
	delete(shader);
}

#endif