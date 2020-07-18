#ifndef PERHAPS_MANAGED_BINDING
#define PERHAPS_MANAGED_BINDING
#include "../../PerhapsPch.h"
#include "../MonoBindings/MonoHaps.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Rendererbase.h"
#include "../Graphics/Renderer2D.h"
#include "../Graphics/ScreenQuadRenderer.h"
#include "../Graphics/ImGui/RendererImGui.h"

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
			imguiRenderer = new RendererImGui();

			mainRt->AttachColorTexture();
			mainRt->AttachDepthStencilBuffer();


			RendererBase::RegisterRenderer(renderer2D, 1);

			#ifdef _DEBUG
			RendererBase::RegisterRenderer(imguiRenderer, 3);
			#else
			RendererBase::RegisterRenderer(scr, 2);
			#endif

			MonoHaps::InitializeMono();
		}

		static void OnUpdate()
		{
			MonoHaps::UpdateManaged();
			RendererBase::RunRenderers(*mainRt);
		}

		static void Cleanup()
		{
			RendererBase::Cleanup();
			delete(renderer2D);
			delete(scr);
			delete(imguiRenderer);
		}
	private:
		static RenderTexture* mainRt;
		static Renderer2D* renderer2D;
		static ScreenQuadRenderer* scr;
		static RendererImGui* imguiRenderer;
	};
}

#endif