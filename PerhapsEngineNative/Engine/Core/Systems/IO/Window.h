#ifndef PERHAPS_WINDOW
#define PERHAPS_WINDOW
#include "../../PerhapsPch.h"
#include "../EventSystem/EventSystem.h"
#include "../EventSystem/EngineEvents.h"

namespace Perhaps
{
	class Window
	{
	public:

		static Window* CreateWindow(int startWidth, int startHeight, const char* title)
		{
			Window* window = new Window(startWidth, startHeight, title);
			activeWindows.insert(std::make_pair(window->glfwWindow, window));

			return window;
		}

		bool WindowCloseRequested();
		void PollEvents();
		void SwapBuffers();
		glm::vec2 GetDimensions();
		GLFWwindow* GetGLFWWindow();

	private:
		static std::map<GLFWwindow*, Window*> activeWindows;
		int mWidth, mHeight;
		GLFWwindow* glfwWindow = nullptr;

		const int GLMajor = 4, GLMinor = 3;
		static bool glfwInitialized;

		Window(int width, int height, const char* title);
		~Window();
		void InitializeGlfw();

		static void OnResize(GLFWwindow* glfwWindow, int width, int height)
		{
			Window* window = activeWindows[glfwWindow];

			window->mWidth = width;
			window->mHeight = height;

			ResizeEvent e;
			e.newSize = window->GetDimensions();
			e.window = window;

			EventDispatcher::DispatchEvent(e);
		}

		static void Error_Callback(int error, const char* description)
		{
			conlog("GLFW Error code: " << error << " Reason: " << description);
		}
	};
}

#endif