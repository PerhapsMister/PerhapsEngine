#ifndef PERHAPS_RESIZE_EVENT
#define PERHAPS_RESIZE_EVENT
#include "EventSystem.h"
#include "../Graphics/RenderTexture.h"

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
			RenderTexture* rt;

			static constexpr const char* descriptor = "ImGuiRender";
			virtual DescriptorType GetType() const
			{
				return descriptor;
			}
	};

	class KeyEvent : public Event
	{
		public:
			GLFWwindow* window; 
			int key;
			int scancode;
			int action;
			int mods;

			static constexpr const char* descriptor = "KeyPress";
			virtual DescriptorType GetType() const
			{
				return descriptor;
			}
	};
}
#endif