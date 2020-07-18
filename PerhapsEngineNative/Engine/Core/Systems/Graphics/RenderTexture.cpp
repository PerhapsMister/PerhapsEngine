#include "RenderTexture.h"

namespace Perhaps
{
	RenderTexture* RenderTexture::bound = nullptr;

	void RenderTexture::AttachDepthStencilBuffer()
	{
		if (rbo == 0)
		{
			InitRbo();
		}

		BindCheck();
	}

	void RenderTexture::AttachColorTexture()
	{
		if (!initialized)
		{
			InitFbo();
		}

		colorTexture = new Texture2D(mWidth, mHeight);
		colorTexture->format = Texture2D::TextureFormat::RGB;
		colorTexture->Apply();

		int texId = colorTexture->GetId();
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId, 0);
		BindCheck();
	}


	bool RenderTexture::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			conlog("Fbo incomplete! Enum: " << status);
			return false;
		}

		if (colorTexture != nullptr)
			colorTexture->Unbind();

		return true;
	}

	void RenderTexture::InitRbo()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RenderTexture::BindCheck()
	{
		if (bound != nullptr)
		{
			bound->Bind();
		}
		else
		{
			Unbind();
		}
	}

	void RenderTexture::Blit(RenderTexture& sender, RenderTexture& receiver, Graphics::ColorMask color, Texture2D::FilterMode mode)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, sender.fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, receiver.fbo);
		glBlitFramebuffer(0, 0, sender.mWidth, sender.mHeight, 0, 0, receiver.mWidth, receiver.mHeight, (GLbitfield)color, (GLenum)mode);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		receiver.BindCheck();
	}

	glm::vec2 RenderTexture::GetDimensions() const
	{
		return glm::vec2(mWidth, mHeight);
	}

	void RenderTexture::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Texture2D* RenderTexture::GetColorAttachment() const
	{
		return colorTexture;
	}


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