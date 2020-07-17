#include "Graphics.h"

namespace Perhaps
{
	PAPI void Graphics_Clear(Graphics::ColorMask mask)
	{
		Graphics::Clear(mask);
	}

	PAPI void Graphics_SetClearColor(Color color)
	{
		Graphics::SetClearColor(color);
	}

	PAPI void Graphics_Draw(VertexArray* va)
	{
		Graphics::Draw(*va);
	}

	PAPI void Graphics_Enable(Graphics::EnableParam param, bool value)
	{
		Graphics::Enable(param, value);
	}
}