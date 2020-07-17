#ifndef PERHAPS_RENDER_TEXTURE
#define PERHAPS_RENDER_TEXTURE
#include "../../PerhapsPch.h"
#include "Texture2D.h"
#include "Graphics.h"

namespace Perhaps
{
	class Graphics;

	class RenderTexture
	{
	public:

		RenderTexture(int width, int height) : mWidth(width), mHeight(height) {}

		void AttachColorTexture()
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

		void AttachDepthStencilBuffer()
		{
			if (rbo == 0)
			{
				InitRbo();
			}

			BindCheck();
		}

		bool Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		 	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			if (status != GL_FRAMEBUFFER_COMPLETE)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				conlog("Fbo incomplete! Enum: " << status);
				return false;
			}

			if(colorTexture != nullptr)
				colorTexture->Unbind();

			return true;
		}

		static void Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		Texture2D* GetColorAttachment() const
		{
			return colorTexture;
		}

		/// <summary>
		/// Copy the contents of one render texture onto another.
		/// </summary>
		/// <param name="sender">The data source</param>
		/// <param name="receiver">The data destination</param>
		/// <param name="color">What textures to copy</param>
		/// <param name="mode">Scaling algorithm</param>
		static void Blit(RenderTexture& sender, RenderTexture& receiver, Graphics::ColorMask color, Texture2D::FilterMode mode)
		{
			glBindFramebuffer(GL_READ_FRAMEBUFFER, sender.fbo);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, receiver.fbo);
			glBlitFramebuffer(0,0, sender.mWidth, sender.mHeight, 0,0, receiver.mWidth, receiver.mHeight, (GLbitfield)color, (GLenum)mode);

			glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

			receiver.BindCheck();
		}

	private:
		unsigned int fbo = 0, rbo = 0;
		int mWidth, mHeight;
		static RenderTexture* bound;

		bool initialized = fbo != 0;

		void InitFbo()
		{
			glGenFramebuffers(1, &fbo);
		}

		void InitRbo()
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

		Texture2D* colorTexture = nullptr;
	};

	
	PAPI RenderTexture* RenderTexture_Create(int width, int height);
	PAPI void RenderTexture_Delete(RenderTexture* rt);
	PAPI bool RenderTexture_Bind(RenderTexture* rt);
	PAPI void RenderTexture_UnBind();
	PAPI void RenderTexture_AttachColorTexture(RenderTexture* rt);
	PAPI void RenderTexture_AttachDepthStencilBuffer(RenderTexture* rt);
	PAPI Texture2D* RenderTexture_GetColorAttachment(RenderTexture* rt);
}

#endif