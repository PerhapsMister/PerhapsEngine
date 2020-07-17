#include "EventSystem.h"

namespace Perhaps
{
	std::map<Event::DescriptorType, std::vector<EventDispatcher::StoredFunction*>> EventDispatcher::observers;
	std::map<int, EventDispatcher::StoredFunction*> EventDispatcher::idToFun;
	int EventDispatcher::idReel;
}