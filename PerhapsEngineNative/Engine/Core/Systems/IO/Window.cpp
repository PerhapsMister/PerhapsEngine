#include "Window.h"

namespace Perhaps
{
	std::map<GLFWwindow*, Window*> Window::activeWindows;
	bool Window::glfwInitialized = false;
}