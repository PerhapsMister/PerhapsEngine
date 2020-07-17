#ifndef PERHAPS_ENGINE
#define PERHAPS_ENGINE
#include "PerhapsPch.h"
#include "Systems/IO/Window.h"
#include "Systems/GameLoop/GameLoop.h"

namespace Perhaps
{

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

		void Begin();
	};
}

#endif