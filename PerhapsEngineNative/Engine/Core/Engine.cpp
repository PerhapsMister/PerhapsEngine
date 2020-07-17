#include "Engine.h"

namespace Perhaps
{
	PerhapsEngine* PerhapsEngine::instance = nullptr;

	void PerhapsEngine::Begin()
	{
		const int width = 1280, height = 720;
		const char* title = "Perhaps Engine";

		mainWindow = Window::CreateWindow(width, height, title);
		GameLoop::Init();

		while (!mainWindow->WindowCloseRequested())
		{
			mainWindow->PollEvents();
			GameLoop::OnUpdate();
			mainWindow->SwapBuffers();
		}


		GameLoop::Cleanup();
	}
}