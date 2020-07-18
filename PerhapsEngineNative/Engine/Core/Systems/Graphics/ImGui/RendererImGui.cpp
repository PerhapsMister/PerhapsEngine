#include "RendererImGui.h"
#include "../../../Application.h"
#include "../../EventSystem/EventSystem.h"
#include "../../EventSystem/EngineEvents.h"
#include "../../Tools/Utils.h"

namespace Perhaps
{
	void RendererImGui::Initialize()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		Window* window = Application::GetInstance()->GetWindow();
		ImGui_ImplGlfw_InitForOpenGL(window->GetGLFWWindow(), true);

		const char* glsl_version = "#version 430 core";
		ImGui_ImplOpenGL3_Init(glsl_version);

		conlog(std::filesystem::current_path().string());
	}

	void RendererImGui::Render(RenderTexture& gameRender)
	{
		RenderTexture::Unbind();
		Graphics::SetClearColor(Color(0, 0, 0, 0));
		Graphics::Clear(Graphics::ColorMask::COLOR);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuiIO& io = ImGui::GetIO();

		/* vvv Fullscreen docking setup  vvv */

		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoScrollbar;
		window_flags |= ImGuiWindowFlags_NoScrollWithMouse;

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		static bool open = true;
		ImGui::Begin("Docking", &open, window_flags);
		ImGui::PopStyleVar();
		ImGui::PopStyleVar(2);

		ImGuiID dockspace_id = ImGui::GetID("FullscreenDock");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

		/* ^^^ Fullscreen docking setup  ^^^ */

		/* vvv Start rendering app vvv */

		ImGuiRenderEvent renderEvent;
		EventDispatcher::DispatchEvent(renderEvent);

		static bool styleEditor = false;
		static bool showScene = true;
		static bool buildWindow = false;
		if (ImGui::BeginMenuBar())
		{

			if (ImGui::BeginMenu("Windows"))
			{
				if (ImGui::MenuItem("Style Editor"))
				{
					styleEditor = !styleEditor;
				}

				if (ImGui::MenuItem("Scene Window"))
				{
					showScene = !showScene;
				}

				if (ImGui::MenuItem("Build Window"))
				{
					buildWindow = !buildWindow;
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		if (showScene)
		{		
			static ImGuiWindowFlags sceneWindowFlags = ImGuiDockNodeFlags_None;
			sceneWindowFlags |= ImGuiWindowFlags_NoCollapse;

			static bool showScene = true;
			if (ImGui::Begin("Game  Scene", &showScene, sceneWindowFlags))
			{

				bool docked = ImGui::IsWindowDocked();
				ImGui::BeginGroup();

				if (ImGui::Button("Enter Play Mode"))
				{

				}

				ImGui::SameLine();

				if (!docked && ImGui::Button("Resize to aspect"))
				{
					glm::vec2 dimensions = gameRender.GetDimensions();
					float aspect = dimensions.x / dimensions.y;
					ImVec2 wsize = ImGui::GetWindowSize();
					if (wsize.x > wsize.y)
					{
						wsize.y = wsize.x / aspect;
					}
					else
					{
						wsize.x = wsize.y * aspect;
					}

					ImGui::SetWindowSize(wsize);
				}

				ImGui::EndGroup();

				if (ImGui::BeginChild("Game Render"))
				{
					ImVec2 wsize = ImGui::GetWindowSize();

					ImGui::Image((ImTextureID)gameRender.GetColorAttachment()->GetId(), wsize, ImVec2(0, 1), ImVec2(1, 0));
					ImGui::EndChild();
				}

				ImGui::End();
			}
		}

		if (styleEditor)
		{
			ImGui::Begin("Editor Styles");
			ImGui::ShowStyleEditor();
			ImGui::End();
		}


		if (ImGui::Begin("FileSystem"))
		{
			std::string root = "D:\\Dev\\Dev\\PerhapsEngine\\PerhapsEngineNative\\Build-Debug-Bin";
			ImGui::Text(root.c_str());


			if (ImGui::TreeNode("File view"))
			{


				ImGui::TreePop();
			}

			ImGui::End();
		}

		if (ImGui::Begin("Scene Hierarchy"))
		{
			ImGui::End();
		}

		if (ImGui::Begin("Inspector"))
		{
			ImGui::End();
		}

		if (ImGui::Begin("Console"))
		{
			ImGui::End();
		}

		/* ^^^ End rendering app ^^^ */
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		ImGui::EndFrame();
	}

	void RendererImGui::Cleanup()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}