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

		bool WindowCloseRequested()
		{
			return glfwWindowShouldClose(glfwWindow);
		}

		void PollEvents()
		{
			glfwPollEvents();
		}

		void SwapBuffers()
		{
			glfwSwapBuffers(glfwWindow);
		}

		glm::vec2 GetDimensions()
		{
			return glm::vec2(mWidth, mHeight);
		}

	private:
		static std::map<GLFWwindow*, Window*> activeWindows;
		int mWidth, mHeight;
		GLFWwindow* glfwWindow = nullptr;

		const int GLMajor = 4, GLMinor = 3;
		static bool glfwInitialized;

		Window(int width, int height, const char* title) : mWidth(width), mHeight(height)
		{
			if (!glfwInitialized)
			{
				InitializeGlfw();
			}
			glfwWindow = glfwCreateWindow(width, height, title, NULL, nullptr);
			glfwMakeContextCurrent(glfwWindow);


			if (!glfwInitialized)
			{
				if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
				{
					conlog("Failed to initialize glad!");
				}
				glfwInitialized = true;

				std::stringstream ss;
				ss << "GPU: " << glGetString(GL_RENDERER) << " by " << glGetString(GL_VENDOR) << "\n";
				ss << "OpenGL Version: " << glGetString(GL_VERSION);
				conlog(ss.str());
			}

			glfwSetFramebufferSizeCallback(glfwWindow, OnResize);
		}

		~Window()
		{
			activeWindows.erase(glfwWindow);
			glfwDestroyWindow(glfwWindow);
		}

		void InitializeGlfw()
		{
			if (!glfwInit())
			{
				conlog("Failed to initialize GLFW");
				return;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLMajor);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLMinor);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}

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
	};
}

#endif