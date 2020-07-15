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
			CreateRenderTexture(width, height);
		}

		~RenderTexture()
		{
			if (bound == this)
				Unbind();

			glDeleteFramebuffers(1, &fbo);
			delete(colorAttachment);
			delete(depthAttachment);
		}

		bool Bind()
		{
			if(fbo == 0)
				return false;

			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			bound = this;
			return true;
		}

		static void Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			bound = nullptr;
		}

		Texture2D* const GetColorTexture() const
		{
			return colorAttachment;
		}

		Texture2D* const GetDepthTexture() const
		{
			return depthAttachment;
		}

	private:
		static RenderTexture* bound;

		void CreateRenderTexture(int width, int height)
		{
			glGenFramebuffers(1, &fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				conlog("Framebuffer incomplete!");
			}

			if(bound != nullptr)
				bound->Bind();
		}

		Texture2D* colorAttachment;
		Texture2D* depthAttachment;
		unsigned int fbo = 0;
	};
	RenderTexture* RenderTexture::bound = nullptr;
}

#endif