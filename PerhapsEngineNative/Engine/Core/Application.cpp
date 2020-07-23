#include "Application.h"
#include "Systems/MonoBindings/ManagedRuntime.h"

#include "Systems/GameLoop/GameLoop.h"
#include "Systems/GameLoop/Scene.h"

#include "Systems/Graphics/Graphics.h"
#include "Systems/Graphics/Rendererbase.h"
#include "Systems/Graphics/Renderer2D.h"
#include "Systems/Graphics/ScreenQuadRenderer.h"
#include "Systems/Graphics/ImGui/RendererImGui.h"

namespace Perhaps
{
	Application* Application::instance = nullptr;

	void Application::Start(int argc, char** argv)
	{
		passert(instance == nullptr, "Application::Start() may only be called once!");
		Application app;
		app.arguments = std::vector<std::string>(argv, argv + argc);
		conlog(app.arguments[0]);

		std::string pathArg = app.arguments[0];
		size_t index = pathArg.find_last_of("\\");
		pathArg.erase(pathArg.begin() + index, pathArg.end());
		conlog("Executing directory: " << pathArg);
		app.executingDirectory = pathArg;

		app.arguments.erase(app.arguments.begin());

		instance = &app;
		instance->Begin();
	}

	const std::vector<std::string>& Application::GetArguments() const
	{
		return arguments;
	}

	const std::string& Application::GetAppDirectory() const
	{
		return executingDirectory;
	}

	Application* Application::GetInstance()
	{
		return instance;
	}

	
	const int width = 1280, height = 720;
	const char* title = "Perhaps Engine";
	void Application::Begin()
	{
		mainWindow = Window::Create(width, height, title);
		
		GameLoop gameloop;
		gameloop.Initialize();

		while (!mainWindow->WindowCloseRequested())
		{
			mainWindow->PollEvents();

			gameloop.Update();

			mainWindow->SwapBuffers();
		}

		gameloop.CleanUp();
		Window::Destroy(mainWindow);
	}

	Window* Application::GetWindow()
	{
		return mainWindow;
	}

	Window* App_GetWindow(Application* app)
	{
		return app->GetWindow();
	}
}