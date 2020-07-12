#ifndef PERHAPS_RESIZE_EVENT
#define PERHAPS_RESIZE_EVENT
#include "EventSystem.h"

class ResizeEvent : public Event
{
public:
	glm::vec2 newSize;

	static constexpr const char* descriptor = "Resize";

	virtual DescriptorType GetType() const
	{
		return descriptor;
	}
};

#endif