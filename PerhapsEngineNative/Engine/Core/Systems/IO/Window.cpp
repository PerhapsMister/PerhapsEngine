#include "Window.h"

namespace Perhaps
{
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

	std::map<GLFWwindow*, Window*> Window::activeWindows;
	bool Window::glfwInitialized = false;
}