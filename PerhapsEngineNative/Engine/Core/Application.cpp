#include "Application.h"

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

	void Application::Begin()
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

	Window* Application::GetWindow()
	{
		return mainWindow;
	}

	Window* App_GetWindow(Application* app)
	{
		return app->GetWindow();
	}
}