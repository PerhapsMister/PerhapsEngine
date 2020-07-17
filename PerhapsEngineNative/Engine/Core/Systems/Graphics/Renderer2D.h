#ifndef PERHAPS_RENDERER_2D
#define PERHAPS_RENDERER_2D
#include "../../PerhapsPch.h"
#include "Graphics.h"
#include "Renderer.h"
#include "Shader.h"
#include "../Assets/Importer.h"
#include "RenderTexture.h"

namespace Perhaps
{
	class Renderer2D : public Renderer
	{
	public:
		VertexArray va;
		Texture2D* shrek;
		Shader* shader;

		void Initialize();
		void Render(RenderTexture& rt);
		void OnCleanup();
	};
}

#endif