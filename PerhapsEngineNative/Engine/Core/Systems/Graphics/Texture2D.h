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
			RGB8 = GL_RGB8,
			RGBA8 = GL_RGBA8,
		};

		enum class WrapMode
		{
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			REPEAT = GL_REPEAT,
			REPEAT_MIRRORED = GL_MIRRORED_REPEAT,
		};

		enum class FilterMode
		{
			POINT = GL_NEAREST,
			LINEAR = GL_LINEAR,
			MIPMAP_POINT = GL_NEAREST_MIPMAP_NEAREST,
			MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
		};
		TextureFormat format = TextureFormat::RGBA;
		WrapMode wrapMode = WrapMode::REPEAT;
		FilterMode filterMode = FilterMode::LINEAR;
		bool generateMips = false;


		Texture2D(int width, int height) : mWidth(width), mHeight(height)
		{
		}

		Texture2D(int width, int height, unsigned char* pixelData, int nrChannels)
		{
			mWidth = width;
			mHeight = height;
			InitTex(pixelData, nrChannels);
		}

		~Texture2D()
		{
			Unbind();
		}
		
		void Apply()
		{
			if (id == 0)
			{
				InitTex();
			}

			glBindTexture(GL_TEXTURE_2D, id);
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

		const int range = 31;
		/// <summary>
		/// Binds a texture to a slot, replacing any texture bound to the slot.
		/// </summary>
		/// <param name="slot"></param>
		/// <returns></returns>
		bool Bind(int slot)
		{
			if (slot > range || slot < 0)
			{
				conlog("Texture slot " << slot << " is out of range.");
				return false;
			}

			GLenum enumSlot = MapSlot(slot);
			boundSlot = slot;
			glActiveTexture(enumSlot);
			if (boundTextures.find(slot) != boundTextures.end())
			{
				if (boundTextures[slot] != nullptr && boundTextures[slot] != this)
				{
					boundTextures[slot]->Unbind();
					boundTextures.erase(slot);
					boundTextures.insert(std::make_pair(slot, this));
				}
			}
			glBindTexture(GL_TEXTURE_2D, id);
			return true;
		}

		void Unbind()
		{
			if (boundSlot != -1)
			{
				boundTextures.erase(boundSlot);

				GLenum enumSlot = MapSlot(boundSlot);
				glActiveTexture(enumSlot);
				boundSlot = -1;
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		static void UnbindAll()
		{
			for(auto&& [lhs,rhs] : boundTextures)
			{
				rhs->SimpleUnbind();
			}

			boundTextures.clear();
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

		static std::unordered_map<int, Texture2D*> boundTextures;
		int mWidth = 0, mHeight = 0;
		unsigned int id = 0;
		int boundSlot = -1;

		static GLenum MapSlot(int index)
		{
			GLenum slot = GL_TEXTURE0 + index;
			return slot;
		}

		/// <summary>
		/// Unbind, but dont touch boundTextures
		/// </summary>
		void SimpleUnbind() 
		{
			if (boundSlot > -1)
			{
				GLenum enumSlot = MapSlot(boundSlot);
				glActiveTexture(enumSlot);
				glBindTexture(GL_TEXTURE_2D, 0);
				boundSlot = -1;
			}
		}

		void InitTex()
		{
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)format, mWidth, mHeight, 0, (GLenum)format, GL_UNSIGNED_BYTE, NULL);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void InitTex(unsigned char* data, int nrChannels)
		{
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			switch (nrChannels)
			{
			case 3:
				format = TextureFormat::RGB;
			default:
				break;
				format = TextureFormat::RGBA;
			case 4:
				break;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)format, mWidth, mHeight, 0, (GLenum)format, GL_UNSIGNED_BYTE, data);
		}
	};

	PAPI Texture2D* Texture2D_Create(int width, int height);
	PAPI void Texture2D_Delete(Texture2D* tex);
	PAPI int Texture2D_GetWrapMode(Texture2D* tex);
	PAPI void Texture2D_SetWrapMode(Texture2D* tex, Texture2D::WrapMode mode);
	PAPI int Texture2D_GetFilterMode(Texture2D* tex);
	PAPI void Texture2D_SetFilterMode(Texture2D* tex, Texture2D::FilterMode mode);
	PAPI int Texture2D_GetFormat(Texture2D* tex);
	PAPI void Texture2D_SetFormat(Texture2D* tex, Texture2D::TextureFormat format);
	PAPI void Texture2D_Apply(Texture2D* tex);
	PAPI void Texture2D_Bind_Slot(Texture2D* tex, int slot);
	PAPI void Texture2D_UnBind(Texture2D* tex);
	PAPI void Texture2D_UnBindAll();
	PAPI void Texture2D_GetDimensions(Texture2D* tex, glm::vec2* vec);
}
#endif