#include "EventSystem.h"

namespace Perhaps
{
	std::map<Event::DescriptorType, std::vector<EventDispatcher::StoredFunction*>> EventDispatcher::observers;
	std::map<size_t, EventDispatcher::StoredFunction*> EventDispatcher::idToFun;
	size_t EventDispatcher::idReel;
}