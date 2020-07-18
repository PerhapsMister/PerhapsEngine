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

		void AttachColorTexture();
		void AttachDepthStencilBuffer();
		bool Bind();
		static void Unbind();
		Texture2D* GetColorAttachment() const;
		glm::vec2 GetDimensions() const;

		/// <summary>
		/// Copy the contents of one render texture onto another.
		/// </summary>
		/// <param name="sender">The data source</param>
		/// <param name="receiver">The data destination</param>
		/// <param name="color">What textures to copy</param>
		/// <param name="mode">Scaling algorithm</param>
		static void Blit(RenderTexture& sender, RenderTexture& receiver, Graphics::ColorMask color, Texture2D::FilterMode mode);

	private:
		unsigned int fbo = 0, rbo = 0;
		int mWidth, mHeight;
		static RenderTexture* bound;

		bool initialized = fbo != 0;

		void InitFbo()
		{
			glGenFramebuffers(1, &fbo);
		}

		void InitRbo();
		void BindCheck();

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