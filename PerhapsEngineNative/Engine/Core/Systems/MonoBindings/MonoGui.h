#ifndef PERHAPS_MONO_GUI
#define PERHAPS_MONO_GUI
#include "../../PerhapsPch.h"

namespace Perhaps
{
	PAPI bool PBegin(const char* name, bool* open, ImGuiWindowFlags flags)
	{
		return ImGui::Begin(name, open, flags);
	}
	PAPI void PEnd()
	{
		ImGui::End();
	}
	PAPI bool PBeginMenuBar()
	{
		return ImGui::BeginMenuBar();
	}
	PAPI void PEndMenuBar()
	{
		ImGui::EndMenuBar();
	}
	PAPI bool PBeginMenu(const char* name)
	{
		return ImGui::BeginMenu(name);
	}
	PAPI void PEndMenu()
	{
		ImGui::EndMenu();
	}
	PAPI bool PMenuItem(const char* name)
	{
		return ImGui::MenuItem(name);
	}

	PAPI bool PBeginChild(const char* name, ImGuiWindowFlags flags, glm::vec2 size, bool border)
	{
		ImVec2 imSize(size.x, size.y);
		return ImGui::BeginChild(name, imSize, border, flags);
	}
	PAPI void PEndChild()
	{
		ImGui::EndChild();
	}


	PAPI void PImage(Texture2D* tex, const glm::vec2& size, const glm::vec2& uv0, const glm::vec2& uv1)
	{
		ImGui::Image((ImTextureID)tex->GetId(), ImVec2(size.x, size.y), ImVec2(uv0.x, uv0.y), ImVec2(uv1.x, uv1.y));
	}
}

#endif