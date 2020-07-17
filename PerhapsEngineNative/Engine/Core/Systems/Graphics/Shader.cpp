#include "Shader.h"

namespace Perhaps
{
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