#ifndef PERHAPS_GAMELOOP
#define PERHAPS_GAMELOOP
#include "../../PerhapsPch.h"

/*
#include "../MonoBindings/MonoHaps.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Rendererbase.h"
#include "../Graphics/Renderer2D.h"
#include "../Graphics/ScreenQuadRenderer.h"
#include "../Graphics/ImGui/RendererImGui.h"
#include "Scene.h"
*/

namespace Perhaps
{
	class ScreenQuadRenderer;

	/// <summary>
	/// Encapsulates the runtime loop.
	/// May be implemented differently depending on the platform.
	/// </summary>
	class GameLoop
	{
	public:
		void Initialize();
		void Update();
		void CleanUp();

		/*
			GameLoop()
			{


			void Initialize()
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
				scene.Initialize();
			}

			void OnUpdate()
			{
				//MonoHaps::UpdateManaged();
				RendererBase::RunRenderers(*mainRt);
				scene.Update();
			}

			void Cleanup()
			{
				RendererBase::Cleanup();
				delete(renderer2D);
				delete(scr);
				delete(imguiRenderer);
			}
		private:

			RenderTexture* mainRt;
			Renderer2D* renderer2D;
			ScreenQuadRenderer* scr;
			RendererImGui* imguiRenderer;
			Scene scene;
			*/
	};
}

#endif