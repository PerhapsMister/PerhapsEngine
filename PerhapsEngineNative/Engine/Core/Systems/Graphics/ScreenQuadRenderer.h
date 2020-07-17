#ifndef PERHAPS_SCREEN_RENDERER
#define PERHAPS_SCREEN_RENDERER
#include "../../PerhapsPch.h"
#include "Graphics.h"
#include "Renderer.h"

namespace Perhaps
{
	class ScreenQuadRenderer : public Renderer
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