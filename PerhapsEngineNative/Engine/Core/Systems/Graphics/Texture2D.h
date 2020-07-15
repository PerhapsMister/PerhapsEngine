#ifndef PERHAPS_TEXTURE_2D
#define PERHAPS_TEXTURE_2D
#include "../../PerhapsPch.h"

namespace Perhaps
{
	class Texture2D
	{
	public:
		enum class TextureFormat
		{
			RGBA = GL_RGBA, RGB = GL_RGB
		};

		enum class WrapMode
		{
			CLAMP_TO_BORDER = GL_CLAMP,
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			REPEAT = GL_REPEAT,
			REPEAT_MIRRORED = GL_MIRRORED_REPEAT
		};

		enum class FilterMode
		{
			POINT = GL_NEAREST,
			LINEAR = GL_LINEAR
		};
		TextureFormat format = TextureFormat::RGBA;
		WrapMode wrapMode = WrapMode::REPEAT;
		FilterMode filterMode = FilterMode::LINEAR;

		Texture2D(int width, int height)
		{
			mWidth = width;
			mHeight = height;
		}
		
		void Apply()
		{
			if (id == 0)
			{
				glGenTextures(1, &id);
				glBindTexture(GL_TEXTURE_2D, id);
				glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)format, mWidth, mHeight, 0, (GLenum)format, GL_UNSIGNED_BYTE, 0);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, id);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)wrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)wrapMode);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)filterMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		unsigned int GetGLId()
		{
			return id;
		}

		glm::vec2 GetDimensions() const
		{
			return glm::vec2(mWidth, mHeight);
		}

	private:
		int mWidth = 0, mHeight = 0;
		unsigned int id = 0;
	};

}
#endif