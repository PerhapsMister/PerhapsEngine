using System;
using System.Runtime.InteropServices;
using System.Numerics;

namespace Perhaps.Engine
{
	/// <summary>
	/// In charge of rendering the editor.
	/// </summary>
    public class EditorRenderer
    {
        RenderTexture rt;

        public EditorRenderer(IntPtr nativeRenderTexture)
        {
            rt = new RenderTexture(nativeRenderTexture);
        }

		bool showScene = true;
		bool buildWindow = false;

		public void Render()
        {
			if (ImGui.BeginMenuBar())
			{
				if (ImGui.BeginMenu("Windows"))
				{
					if (ImGui.MenuItem("Scene Window"))
					{
						showScene = !showScene;
					}


					ImGui.EndMenu();
				}

				ImGui.EndMenuBar();
			}

			if (showScene)
			{
				ImGuiWindowFlags flags = ImGuiWindowFlags.ImGuiWindowFlags_None;
				flags |= ImGuiWindowFlags.ImGuiWindowFlags_NoCollapse;

				if (ImGui.Begin("Show Scene", ref showScene, flags))
				{
					ImGui.BeginChild("Game Render");
					ImGui.EndChild();

					/*
						if (ImGui.BeginChild("Game Render"))
						{
							ImVec2 wsize = ImGui::GetWindowSize();

							ImGui::Image((ImTextureID)gameRender.GetColorAttachment()->GetId(), wsize, ImVec2(0, 1), ImVec2(1, 0));
							ImGui::EndChild();
						}
						*/
					ImGui.End();
				}
			}
		}


		/*
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

		if (styleEditor && ImGui::Begin("Editor Styles"))
		{
			ImGui::ShowStyleEditor();
			ImGui::End();
		}


		if (ImGui::Begin("FileSystem"))
		{
			std::string root = "D:\\Dev\\Dev\\PerhapsEngine\\PerhapsEngineNative\\Build-Debug-Bin";
			ImGui::Text(root.c_str());

			if (ImGui::TreeNode("File view"))
			{
				const int max_columns = 2;

				std::vector<std::string> files =
				{
					"hello.h",
					"hello.cpp",
					"vertex.shader",
					"fragment.shader",
					"shrek.png"
				};
				static int selectedIndex = -1;

				ImGui::Columns(max_columns, NULL, true);
				for (size_t i = 0; i < files.size(); i++)
				{

					ImGui::PushID(i);

					const char* file = files[i].c_str();
					if (ImGui::Selectable(file, selectedIndex == i))
					{
						selectedIndex = i;
						ImGui::CloseCurrentPopup();
					}

					if (ImGui::IsItemClicked(1))
					{
						ImGui::OpenPopup("file_popup");
					}

					if (ImGui::BeginPopup("file_popup"))
					{
						ImGui::MenuItem(file, NULL, false, false);

						if (ImGui::MenuItem("Rename"))
						{

						}

						if (ImGui::MenuItem("Delete"))
						{

						}

						ImGui::EndPopup();
					}

					if (ImGui::BeginDragDropSource())
					{
						ImGui::SetDragDropPayload("sa", NULL, NULL);
						ImGui::Text(file);

						ImGui::EndDragDropSource();
					}
					if (ImGui::BeginDragDropTarget())
					{
						if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("sa"))
						{

						}

						ImGui::EndDragDropTarget();
					}

					ImGui::PopID();

					ImGui::NextColumn();
				}
				ImGui::Columns(1);
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
         
         */
	}


}
