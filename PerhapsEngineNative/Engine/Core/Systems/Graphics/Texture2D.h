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
			RGBA = GL_RGBA, RGB = GL_RGB,
			DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
		};

		enum class WrapMode
		{
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
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
		bool generateMips = false;

		Texture2D(int width, int height)
		{
			mWidth = width;
			mHeight = height;
		}

		void LoadPixels(void* source)
		{
			if (id != 0)
			{
				conlog("Texture2D already initialized - cannot LoadPixels().");
				return;
			}

			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)format, mWidth, mHeight, 0, (GLenum)format, GL_UNSIGNED_BYTE, source);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		
		void Apply()
		{
			if (id == 0)
			{
				glGenTextures(1, &id);
				glBindTexture(GL_TEXTURE_2D, id);
				glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)format, mWidth, mHeight, 0, (GLenum)format, GL_UNSIGNED_BYTE, NULL);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, id);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)wrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)wrapMode);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)filterMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			if (generateMips)
			{
				glGenerateMipmap(GL_TEXTURE_2D);
			}

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Bind()
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, id);
		}

		const int range = 31;
		bool Bind(int slot)
		{
			if (slot > range|| slot < 0)
			{
				conlog("Texture slot " << slot << " is out of range.");
				return false;
			}

			GLenum enumSlot = MapSlot(slot);
			boundSlot = slot;
			glActiveTexture(enumSlot);
			glBindTexture(GL_TEXTURE_2D, id);
		}

		void Unbind()
		{
			GLenum enumSlot = MapSlot(boundSlot);
			glActiveTexture(enumSlot);
			boundSlot = 0;
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		static void Unbind(int slot)
		{
			GLenum enumSlot = MapSlot(slot);
			glActiveTexture(enumSlot);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glm::vec2 GetDimensions() const
		{
			return glm::vec2(mWidth, mHeight);
		}

		unsigned int const GetId() const
		{
			return id;
		}

	private:
		int mWidth = 0, mHeight = 0;
		unsigned int id = 0;
		int boundSlot = 0;

		static GLenum MapSlot(int index)
		{
			GLenum slot = GL_TEXTURE0 + index;
			return slot;
		}
	};


	PAPI void Texture2D_LoadPixels(Texture2D* tex, void* data)
	{
		tex->LoadPixels(data);
	}

	PAPI Texture2D* Texture2D_Create(int width, int height)
	{
		Texture2D* tex = new Texture2D(width, height);
		return tex;
	}

	PAPI void Texture2D_Delete(Texture2D* tex)
	{
		delete(tex);
	}

	PAPI int Texture2D_GetWrapMode(Texture2D* tex)
	{
		return (int)tex->wrapMode;
	}

	PAPI void Texture2D_SetWrapMode(Texture2D* tex, Texture2D::WrapMode mode)
	{
		tex->wrapMode = mode;
	}

	PAPI int Texture2D_GetFilterMode(Texture2D* tex)
	{
		return (int)tex->filterMode;
	}

	PAPI void Texture2D_SetFilterMode(Texture2D* tex, Texture2D::FilterMode mode)
	{
		tex->filterMode = mode;
	}


	PAPI int Texture2D_GetFormat(Texture2D* tex)
	{
		return (int)tex->format;
	}

	PAPI void Texture2D_SetFormat(Texture2D* tex, Texture2D::TextureFormat format)
	{
		tex->format = format;
	}

	PAPI void Texture2D_Apply(Texture2D* tex)
	{
		tex->Apply();
	}

	PAPI void Texture2D_Bind(Texture2D* tex)
	{
		tex->Bind();
	}

	PAPI void Texture2D_Bind_Slot(Texture2D* tex, int slot)
	{
		tex->Bind(slot);
	}

	PAPI void Texture2D_UnBind(int slot)
	{
		Texture2D::Unbind(slot);
	}

	PAPI void Texture2D_GetDimensions(Texture2D* tex, glm::vec2* vec)
	{
		*vec = tex->GetDimensions();
	}
}
#endif