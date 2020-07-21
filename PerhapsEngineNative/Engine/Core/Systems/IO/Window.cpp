#include "Window.h"
#include "KeyCodes.h"
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

		glfwSetKeyCallback(glfwWindow, key_callback);
		glfwSetFramebufferSizeCallback(glfwWindow, OnResize);

		EventDispatcher::Subscribe(KeyEvent::descriptor, std::bind(&Window::OnKeyEvent, this, std::placeholders::_1));
	}

	void Window::OnKeyEvent(const Event& e)
	{
		const KeyEvent& keyEvent = (KeyEvent&)e;

		if(keyEvent.action == GLFW_PRESS)
			tappedKeys.insert(keyEvent.key);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		KeyEvent e;
		e.window = window;
		e.key = key;
		e.scancode = scancode;
		e.action = action;
		e.mods = mods;

		EventDispatcher::DispatchEvent(e);
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

	void Window::SetTitle(const char* title)
	{
		glfwSetWindowTitle(glfwWindow, title);
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
		tappedKeys.clear();
		glfwSwapBuffers(glfwWindow);
	}

	glm::vec2 Window::GetDimensions()
	{
		return glm::vec2(mWidth, mHeight);
	}

	bool Window_IsKeyDown(Window* window, KeyCode keycode)
	{
		return window->IsKeyDown(keycode);
	}

	bool Window_IsKeyTapped(Window* window, KeyCode key)
	{
		return window->IsKeyTapped(key);
	}

	void Window_GetDimensions(Window* window, glm::vec2* dims)
	{
		*dims = window->GetDimensions();
	}

	void Window_SetTitle(Window* window, const char* title)
	{
		window->SetTitle(title);
	}

	bool Window::IsKeyDown(const KeyCode& key)
	{
		int castedKey = (int)key;
		int state = glfwGetKey(glfwWindow, castedKey);
		return state == GLFW_PRESS;
	}

	bool Window::IsKeyTapped(const KeyCode& key)
	{
		int castedKey = (int)key;
		return tappedKeys.find(castedKey) != tappedKeys.end();
	}

	std::map<GLFWwindow*, Window*> Window::activeWindows;
	bool Window::glfwInitialized = false;
}