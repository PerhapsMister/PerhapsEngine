#ifndef PERHAPS_SHADER
#define PERHAPS_SHADER
#include "../../PerhapsPch.h"
namespace Perhaps
{
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

		bool IsBound() const
		{
			return bound == this;
		}

		static void Unbind()
		{
			glUseProgram(0);
			bound = nullptr;
		}


		void SetInt(const std::string& name, int value)
		{
			int location = GetLocation(name);
			if (location != -1)
			{
				glUniform1i(location, value);
			}
		}

		void SetFloat(const std::string& name, float value)
		{
			int location = GetLocation(name);
			if (location != -1)
			{
				glUniform1f(location, value);
			}
		}

		void SetMatrix4(const std::string& name, const glm::mat4& matrix)
		{
			int location = GetLocation(name);
			if (location != -1)
			{
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
			}
		}

	private:
		static Shader* bound;
		std::unordered_map<std::string, int> nameToLocation;

		Shader() : programId(-1)
		{

		}

		int GetLocation(const std::string& name)
		{
			if (nameToLocation.find(name) != nameToLocation.end())
			{
				return nameToLocation[name];
			}

			int location = glGetUniformLocation(programId, name.c_str());
			if (location != -1)
			{
				nameToLocation.insert(std::make_pair(name, location));
				return location;
			}

			return -1;
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

	PAPI void Shader_SetInt(Shader* shader, const char* name, int value)
	{
		shader->SetInt(name, value);
	}

	PAPI void Shader_SetFloat(Shader* shader, const char* name, float value)
	{
		shader->SetFloat(name, value);
	}

	PAPI void Shader_SetMatrix4(Shader* shader, const char* name, glm::mat4 matrix)
	{
		shader->SetMatrix4(name, matrix);
	}
}
#endif