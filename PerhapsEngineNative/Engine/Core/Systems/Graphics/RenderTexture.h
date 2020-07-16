#ifndef PERHAPS_RENDER_TEXTURE
#define PERHAPS_RENDER_TEXTURE
#include "../../PerhapsPch.h"
#include "Texture2D.h"

namespace Perhaps
{
	class RenderTexture
	{
	public:
		RenderTexture(int width, int height)
		{
			mWidth = width;
			mHeight = height;
			InitFbo();
		}

		~RenderTexture()
		{
			if (bound == this)
				Unbind();

			glDeleteFramebuffers(1, &fbo);
			delete(colorAttachment);
		}

		void AttachColorTexture()
		{
			colorAttachment = new Texture2D(mWidth, mHeight);
			colorAttachment->format = Texture2D::TextureFormat::RGB;
			colorAttachment->filterMode = Texture2D::FilterMode::LINEAR;
			colorAttachment->generateMips = false;
			colorAttachment->Apply();

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment->GetId(), 0);
		}

		void AttachDepthStencilBuffer()
		{
			if (rbo == 0)
			{
				InitRbo();
			}

			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

			BindCheck();
		}

		bool Bind()
		{
			if(fbo == 0)
				return false;

			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				conlog("Framebuffer incomplete!");
				BindCheck();

				return false;
			}

			bound = this;
			return true;
		}

		static void Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			bound = nullptr;
		}

		Texture2D* GetColorAttachment()
		{
			return colorAttachment;
		}

	private:
		static RenderTexture* bound;
		unsigned int fbo = 0, rbo = 0;
		int mWidth = 0, mHeight = 0;
		Texture2D* colorAttachment;

		void BindCheck()
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


		void InitRbo()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glGenRenderbuffers(1, &rbo);
		}

		void InitFbo()
		{
			glGenFramebuffers(1, &fbo);
		}
	};
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

#endif