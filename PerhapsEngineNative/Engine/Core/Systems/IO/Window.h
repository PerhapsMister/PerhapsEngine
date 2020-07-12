#ifndef PERHAPS_WINDOW
#define PERHAPS_WINDOW
#include "../../PerhapsPch.h"
#include "../EventSystem/EventSystem.h"
#include "../EventSystem/EngineEvents.h"

class Window
{
public:

	static void Initialize(int startWidth, int startHeight, const char* title)
	{
		if (singleton == nullptr)
		{
			Window* window = new Window(startWidth, startHeight, title);
			singleton = window;
		}
	}

	static Window* GetWindow()
	{
		return singleton;
	}

	bool WindowCloseRequested()
	{
		return glfwWindowShouldClose(mWindow);
	}

	void PollEvents()
	{
		glfwPollEvents();
	}

	void SwapBuffers()
	{
		glfwSwapBuffers(mWindow);
	}

	glm::vec2 GetDimensions()
	{
		return glm::vec2(mWidth, mHeight);
	}

	private:
	int mWidth, mHeight;
	static Window* singleton;
	GLFWwindow* mWindow = nullptr;

	const int GLMajor = 4, GLMinor = 3;

	Window(int width, int height, const char* title)
	{
		if (!glfwInit())
		{
			conlog("Failed to initialize GLFW");
			return;
		}
		mWidth = width;
		mHeight = height;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLMinor);
		glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		mWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwMakeContextCurrent(mWindow);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			conlog("Failed to initialize glad!");
		}

		std::stringstream ss;
		ss << "GPU: " << glGetString(GL_RENDERER) << " by " << glGetString(GL_VENDOR) << "\n";
		ss << "OpenGL Version: " << glGetString(GL_VERSION);
		conlog(ss.str());

		glfwSetFramebufferSizeCallback(mWindow, OnResize);
	}

	static void OnResize(GLFWwindow* window, int width, int height)
	{
		singleton->mWidth = width;
		singleton->mHeight = height;

		ResizeEvent e;
		e.newSize = singleton->GetDimensions();
		EventDispatcher::DispatchEvent(e);
	}
};
Window* Window::singleton = nullptr;

#endif