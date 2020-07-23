#include "GameLoop.h"

#include "../Graphics/Graphics.h"
#include "../Graphics/Rendererbase.h"
#include "../Graphics/Renderer2D.h"
#include "../Graphics/ScreenQuadRenderer.h"
#include "../Graphics/ImGui/RendererImGui.h"

#include "../MonoBindings/ManagedRuntime.h"
#include "Scene.h"

namespace Perhaps
{
	Renderer2D *renderer2d;
	RendererImGui* imguiRenderer;
	RenderTexture* rt;

	void GameLoop::Initialize()
	{
		renderer2d = new Renderer2D();
		imguiRenderer = new RendererImGui();

		RendererBase::RegisterRenderer(renderer2d, 1);
		RendererBase::RegisterRenderer(imguiRenderer, 2);

		rt = new RenderTexture(1280, 720);
		rt->AttachColorTexture();
		rt->AttachDepthStencilBuffer();

		const bool debug = false;
		const char* libDir = "C:\\Program Files (x86)\\Mono\\lib";
		const char* etcDir = "C:\\Program Files (x86)\\Mono\\etc";
		MonoRuntime::InitializeMono(debug, libDir, etcDir);
	}

	void GameLoop::Update()
	{
		

		RendererBase::RunRenderers(*rt);
	}

	void GameLoop::CleanUp()
	{
		delete(rt);
		delete(renderer2d);
		delete(imguiRenderer);
	}
}