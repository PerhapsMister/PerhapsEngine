#ifndef PERHAPS_WINDOW
#define PERHAPS_WINDOW
#include "../../PerhapsPch.h"

namespace Perhaps
{
	class Window
	{
	public:

		static Window* CreateWindow(int startWidth, int startHeight, const char* title);

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

		static void OnResize(GLFWwindow* glfwWindow, int width, int height);
		static void Error_Callback(int error, const char* description);
	};

	PAPI void Window_GetDimensions(Window* window, glm::vec2* dims);
}

#endif