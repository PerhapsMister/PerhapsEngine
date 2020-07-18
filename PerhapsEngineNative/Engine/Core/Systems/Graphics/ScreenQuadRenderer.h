#ifndef PERHAPS_SCREEN_RENDERER
#define PERHAPS_SCREEN_RENDERER
#include "../../PerhapsPch.h"
#include "Graphics.h"
#include "RendererBase.h"

namespace Perhaps
{
	class ScreenQuadRenderer : public RendererBase
	{
	public:

		void Initialize();

		void Render(RenderTexture& rt);
		void Cleanup();

		private:
			Shader* screenQuadShader;
			VertexArray* quadVa;		
	};

}

#endif