#ifndef PERHAPS_RESIZE_EVENT
#define PERHAPS_RESIZE_EVENT
#include "EventSystem.h"

class Window;

class ResizeEvent : public Event
{
public:
	Window* window;
	glm::vec2 newSize;

	static constexpr const char* descriptor = "Resize";

	virtual DescriptorType GetType() const
	{
		return descriptor;
	}
};

#endif