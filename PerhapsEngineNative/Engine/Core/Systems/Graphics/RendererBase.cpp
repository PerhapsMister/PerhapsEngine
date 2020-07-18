#include "RendererBase.h"

namespace Perhaps
{
	std::unordered_map<int, RendererBase*> RendererBase::registeredRenderers;
	std::vector<int> RendererBase::registeredPriorities;
}