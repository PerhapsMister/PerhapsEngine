#include "RenderTexture.h"

namespace Perhaps
{
	RenderTexture* RenderTexture::bound = nullptr;

	PAPI RenderTexture* RenderTexture_Create(int width, int height)
	{
		RenderTexture* rt = new RenderTexture(width, height);
		return rt;
	}

	PAPI void RenderTexture_Delete(RenderTexture* rt)
	{
		delete(rt);
	}

	PAPI bool RenderTexture_Bind(RenderTexture* rt)
	{
		return rt->Bind();
	}

	PAPI void RenderTexture_UnBind()
	{
		RenderTexture::Unbind();
	}

	PAPI void RenderTexture_AttachColorTexture(RenderTexture* rt)
	{
		rt->AttachColorTexture();
	}

	PAPI void RenderTexture_AttachDepthStencilBuffer(RenderTexture* rt)
	{
		rt->AttachDepthStencilBuffer();
	}

	PAPI Texture2D* RenderTexture_GetColorAttachment(RenderTexture* rt)
	{
		return rt->GetColorAttachment();
	}
}