#include "GameLoop.h"

namespace Perhaps
{
	Renderer2D* GameLoop::renderer2D = nullptr;
	RenderTexture* GameLoop::mainRt = nullptr;
	ScreenQuadRenderer* GameLoop::scr = nullptr;
}