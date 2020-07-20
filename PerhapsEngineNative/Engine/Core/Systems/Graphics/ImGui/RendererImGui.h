#ifndef PERHAPS_RENDERER_IMGUI
#define PERHAPS_RENDERER_IMGUI
#include "../../../PerhapsPch.h"
#include "../RendererBase.h"
#include "../RenderTexture.h"

namespace Perhaps
{
	class RendererImGui : public RendererBase
	{
		public:

		void Initialize();
		void Render(RenderTexture& rt);
		void Cleanup();

		private:
		void SetupDockspace(bool* p_open);
	};

}
#endif