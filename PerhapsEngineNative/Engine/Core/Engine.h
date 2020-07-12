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

void PrintMethod(MonoString* string)
{
	char* cppString = mono_string_to_utf8(string);

	std::cout << cppString;

	mono_free(cppString);
}

const char* AssembliesFolder = "MonoRuntime/Managed";
const char* EtcFolder = "MonoRuntime/etc";

class PerhapsEngine
{
public:
	static void Initialize()
	{
		PerhapsEngine engine;
		engine.Begin();
	}

private:
	static PerhapsEngine instance;
	friend class Window;

	PerhapsEngine()
	{

	}

	void Begin()
	{
		Window::Initialize(width, height, title);
		Window* window = Window::GetWindow();
		Graphics::SetClearColor(Color(0.4, 0.4, 1, 1));

		std::vector<float> positions =
		{
			-0.5f, -0.5f,//bottom left
			0.5f, -0.5f,//bottom right
			0.5f, 0.5f,//top right
			-0.5f, 0.5f//top left
		};

		std::vector<unsigned int> indices =
		{
			0,1,2,
			2,3,0
		};

		VertexArray va;
		va.positions = positions;
		va.indices = indices;
		va.UploadData();
		va.Bind();

		GameLoop::Init();

		while (!window->WindowCloseRequested())
		{
			window->PollEvents();

			Graphics::Clear(Graphics::ClearMask::COLOR_DEPTH_STENCIL);
			Graphics::Draw(&va);
			GameLoop::OnUpdate();

			window->SwapBuffers();
		}
	}
};


#endif