#ifndef PERHAPS_MANAGED_BINDING
#define PERHAPS_MANAGED_BINDING
#include "../../PerhapsPch.h"
#include "../MonoBindings/MonoHaps.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Renderer2D.h"
#include "../Graphics/ScreenQuadRenderer.h"

namespace Perhaps
{
	class ScreenQuadRenderer;

	class GameLoop
	{
	public:

		static void Init()
		{
			renderer2D = new Renderer2D();
			scr = new ScreenQuadRenderer();
			mainRt = new RenderTexture(1280, 720);
			mainRt->AttachColorTexture();
			mainRt->AttachDepthStencilBuffer();


			Renderer::RegisterRenderer(renderer2D, 1);
			Renderer::RegisterRenderer(scr, 2);
			MonoHaps::InitializeMono();
		}

		static void OnUpdate()
		{
			MonoHaps::UpdateManaged();
			Renderer::RunRenderers(*mainRt);
		}

		static void Cleanup()
		{
			Renderer::Cleanup();
			delete(renderer2D);
		}
	private:
		static Renderer2D* renderer2D;
		static RenderTexture* mainRt;
		static ScreenQuadRenderer* scr;
	};
}

#endif