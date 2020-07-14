#ifndef PERHAPS_ENGINE
#define PERHAPS_ENGINE
#include "PerhapsPch.h"
#include "Systems/Graphics/Graphics.h"
#include "Systems/IO/Window.h"
#include "Systems/Graphics/VertexArray.h"
#include "Systems/EventSystem/EventSystem.h"
#include "Systems/GameLoop/GameLoop.h"

const int width = 1280, height = 720;
const char* title = "Perhaps Engine";

class PerhapsEngine
{
public:
	static void Initialize()
	{
		if (instance == nullptr)
		{
			PerhapsEngine engine;
			instance = &engine;
			engine.Begin();
		}
	}

	static PerhapsEngine* Singleton()
	{
		return instance;
	}

	Window* GetWindow()
	{
		return mainWindow;
	}

private:
	static PerhapsEngine* instance;
	Window* mainWindow;

	void Begin()
	{
		mainWindow = Window::GetWindow(width, height, title);
		GameLoop::Init();

		while (!mainWindow->WindowCloseRequested())
		{
			mainWindow->PollEvents();
			GameLoop::OnUpdate();
			mainWindow->SwapBuffers();
		}

		GameLoop::Cleanup();
	}
};
PerhapsEngine* PerhapsEngine::instance = nullptr;

#endif