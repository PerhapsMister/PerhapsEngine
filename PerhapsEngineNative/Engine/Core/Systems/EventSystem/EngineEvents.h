#ifndef PERHAPS_RESIZE_EVENT
#define PERHAPS_RESIZE_EVENT
#include "EventSystem.h"

namespace Perhaps
{

	class Window;

	class ResizeEvent : public Event
	{
	public:
		Window* window = nullptr;
		glm::vec2 newSize;

		static constexpr const char* descriptor = "Resize";

		virtual DescriptorType GetType() const
		{
			return descriptor;
		}
	};


	class ImGuiRenderEvent : public Event
	{
		public:

			static constexpr const char* descriptor = "ImGuiRender";
			virtual DescriptorType GetType() const
			{
				return descriptor;
			}
	};
}
#endif