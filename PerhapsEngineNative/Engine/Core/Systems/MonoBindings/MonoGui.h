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


	PAPI void PGetWindowSize(glm::vec2* dims)
	{
		ImVec2 size = ImGui::GetWindowSize();
		glm::vec2 sizeVec2 = glm::vec2(size.x, size.y);
		*dims = sizeVec2;
	}

	PAPI bool PIsWindowDocked()
	{
		return ImGui::IsWindowDocked();
	}

	PAPI bool PButton(const char* name)
	{
		return ImGui::Button(name);
	}

	PAPI void PSameLine()
	{
		ImGui::SameLine();
	}

	PAPI void PSetWindowSize(glm::vec2 size)
	{
		ImVec2 imSize = ImVec2(size.x, size.y);
		ImGui::SetWindowSize(imSize);
	}

	PAPI void PBeginGroup()
	{
		ImGui::BeginGroup();
	}

	PAPI void PEndGroup()
	{
		ImGui::EndGroup();
	}

	PAPI void PText(const char* text)
	{
		ImGui::Text(text);
	}

	PAPI bool PTreeNode(const char* name)
	{
		return ImGui::TreeNode(name);
	}
	PAPI void PTreePop()
	{
		ImGui::TreePop();
	}

	PAPI void PColumns(int count, const char* id)
	{
		ImGui::Columns(count, id);
	}
	PAPI void PPushId(int id)
	{
		ImGui::PushID(id);
	}
	PAPI void PPushId_str(const char* id)
	{
		ImGui::PushID(id);
	}
	PAPI void PPopId()
	{
		ImGui::PopID();
	}
	PAPI void PSelectable(const char* name, bool* selected)
	{
		ImGui::Selectable(name, selected);
	}
	PAPI void PSelectable_NotRef(const char* name, bool selected)
	{
		ImGui::Selectable(name, selected);
	}
	PAPI bool PIsItemClicked(int mouseButton)
	{
		return ImGui::IsItemClicked(mouseButton);
	}
	PAPI void POpenPopup(const char* id)
	{
		ImGui::OpenPopup(id);
	}
	PAPI void PCloseCurrentPopup()
	{
		ImGui::CloseCurrentPopup();
	}
	PAPI void PBeginPopup(const char* id, ImGuiWindowFlags flags)
	{
		ImGui::BeginPopup(id, flags);
	}
	PAPI void PEndPopup()
	{
		ImGui::EndPopup();
	}
	PAPI void PBeginDragSource()
	{
		ImGui::BeginDragDropSource();
	}
	PAPI void PEndDragAndDropSource()
	{
		ImGui::EndDragDropSource();
	}
	PAPI bool PBeginDragAndDropTarget()
	{
		return ImGui::BeginDragDropTarget();
	}

	PAPI void PSetDragAndDropPayload(const char* id, int dataId)
	{
		ImGui::SetDragDropPayload(id, &dataId, sizeof(int));
	}

	PAPI bool PAcceptDragAndDropPayload(const char* id, int* dataId)
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(id))
		{
			*dataId = *(int*)payload->Data;
			return true;
		}

		*dataId = 0;
		return false;
	}
	PAPI void PEndDragAndDropTarget()
	{
		ImGui::EndDragDropTarget();
	}
	PAPI void PNextColumn()
	{
		ImGui::NextColumn();
	}

	PAPI bool PInputText(const char* label, char* inputText, int length)
	{
		return ImGui::InputText(label, inputText, length);
	}

	PAPI void PPushItemWidth(float width)
	{
		ImGui::PushItemWidth(width);
	}

	PAPI void PPopItemWidth()
	{
		ImGui::PopItemWidth();
	}

	PAPI void PBullet()
	{
		ImGui::Bullet();
	}

	PAPI void PBulletText(const char* text)
	{
		ImGui::BulletText(text);
	}

	PAPI void PSeparator()
	{
		ImGui::Separator();
	}
}

#endif