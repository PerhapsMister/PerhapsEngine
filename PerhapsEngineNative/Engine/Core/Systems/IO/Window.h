#ifndef PERHAPS_WINDOW
#define PERHAPS_WINDOW
#include "../../PerhapsPch.h"
#include "KeyCodes.h"
#include "../EventSystem/EventSystem.h"
#include "../EventSystem/EngineEvents.h"


namespace Perhaps
{
	class Window
	{
	public:

		static Window* Create(int startWidth, int startHeight, const char* title);
		static void Destroy(Window* window);


		bool WindowCloseRequested();
		void PollEvents();
		void SwapBuffers();
		void SetTitle(const char* title);

		glm::vec2 GetDimensions();
		GLFWwindow* GetGLFWWindow();

		bool IsKeyDown(const KeyCode& key);
		bool IsKeyTapped(const KeyCode& key);
	private:
		static std::map<GLFWwindow*, Window*> activeWindows;
		std::unordered_set<int> tappedKeys;
		int mWidth, mHeight;
		GLFWwindow* glfwWindow = nullptr;

		const int GLMajor = 4, GLMinor = 3;
		static bool glfwInitialized;

		Window(int width, int height, const char* title);
		~Window();
		void InitializeGlfw();
		void OnKeyEvent(const Event& keyEvent);

		static void OnResize(GLFWwindow* glfwWindow, int width, int height);
		static void Error_Callback(int error, const char* description);
	};
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	PAPI void Window_GetDimensions(Window* window, glm::vec2* dims);
	PAPI bool Window_IsKeyDown(Window* window, KeyCode keycode);
	PAPI bool Window_IsKeyTapped(Window* window, KeyCode keycode);
	PAPI void Window_SetTitle(Window* window, const char* title);
}

#endif