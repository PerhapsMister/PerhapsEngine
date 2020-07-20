#include "Window.h"
#include "../EventSystem/EventSystem.h"
#include "../EventSystem/EngineEvents.h"

namespace Perhaps
{
	Window* Window::CreateWindow(int startWidth, int startHeight, const char* title)
	{
		Window* window = new Window(startWidth, startHeight, title);
		activeWindows.insert(std::make_pair(window->glfwWindow, window));

		return window;
	}

	Window::Window(int width, int height, const char* title) : mWidth(width), mHeight(height)
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

	Window::~Window()
	{
		activeWindows.erase(glfwWindow);
		glfwDestroyWindow(glfwWindow);
	}

	GLFWwindow* Window::GetGLFWWindow()
	{
		return glfwWindow;
	}

	void Window::InitializeGlfw()
	{
		glfwSetErrorCallback(Window::Error_Callback);

		if (!glfwInit())
		{
			conlog("Failed to initialize GLFW");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLMinor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void Window::OnResize(GLFWwindow* glfwWindow, int width, int height)
	{
		Window* window = activeWindows[glfwWindow];

		window->mWidth = width;
		window->mHeight = height;

		ResizeEvent e;
		e.newSize = window->GetDimensions();
		e.window = window;

		EventDispatcher::DispatchEvent(e);
	}

	void Window::Error_Callback(int error, const char* description)
	{
		conlog("GLFW Error code: " << error << " Reason: " << description);
	}

	bool Window::WindowCloseRequested()
	{
		return glfwWindowShouldClose(glfwWindow);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(glfwWindow);
	}

	glm::vec2 Window::GetDimensions()
	{
		return glm::vec2(mWidth, mHeight);
	}

	void Window_GetDimensions(Window* window, glm::vec2* dims)
	{
		*dims = window->GetDimensions();
	}

	std::map<GLFWwindow*, Window*> Window::activeWindows;
	bool Window::glfwInitialized = false;
}