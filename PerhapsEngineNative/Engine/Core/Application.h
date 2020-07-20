#ifndef PERHAPS_ENGINE
#define PERHAPS_ENGINE
#include "PerhapsPch.h"
#include "Systems/IO/Window.h"
#include "Systems/GameLoop/GameLoop.h"

namespace Perhaps
{
	class Application
	{
	public:
		Window* GetWindow();
		const std::vector<std::string>& GetArguments() const;
		const std::string& GetAppDirectory() const;

		static Application* GetInstance();
		static void Start(int argc, char** argv);
	private:
		static Application* instance;
		Window* mainWindow = nullptr;
		std::vector<std::string> arguments;
		std::string executingDirectory;

		void Begin();
		Application() {}
	};

	PAPI Window* App_GetWindow(Application* app);
}

#endif