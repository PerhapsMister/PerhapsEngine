#include "Texture2D.h"

namespace Perhaps
{
	std::unordered_map<int, Texture2D*> Texture2D::boundTextures;

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

	PAPI void Texture2D_Bind_Slot(Texture2D* tex, int slot)
	{
		tex->Bind(slot);
	}


	PAPI void Texture2D_UnBind(Texture2D* tex)
	{
		tex->Unbind();
	}

	PAPI void Texture2D_UnBindAll()
	{
		Texture2D::UnbindAll();
	}

	PAPI void Texture2D_GetDimensions(Texture2D* tex, glm::vec2* vec)
	{
		*vec = tex->GetDimensions();
	}
}