#include "RendererImGui.h"
#include "../../../Engine.h"
#include "../../EventSystem/EventSystem.h"
#include "../../EventSystem/EngineEvents.h"

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

		Window* window = PerhapsEngine::GetWindow();
		ImGui_ImplGlfw_InitForOpenGL(window->GetGLFWWindow(), true);

		const char* glsl_version = "#version 430 core";
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void RendererImGui::Render(RenderTexture& rt)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static bool show_demo = true;
		ImGui::ShowDemoWindow(&show_demo);

		ImGuiRenderEvent renderEvent;
		EventDispatcher::DispatchEvent(renderEvent);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
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