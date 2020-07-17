#include "Renderer.h"

namespace Perhaps
{
	std::unordered_map<int, Renderer*> Renderer::registeredRenderers;
	std::vector<int> Renderer::registeredPriorities;
}