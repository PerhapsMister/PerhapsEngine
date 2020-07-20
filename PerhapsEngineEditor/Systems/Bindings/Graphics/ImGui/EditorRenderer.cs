using System;
using System.Runtime.InteropServices;
using System.Numerics;
using System.Collections.Generic;

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

        bool sceneWindow = true;
        bool filesystemWindow = true;
        bool inspectorWindow = true;
        bool sceneGraphWindow = true;

        public void Render()
        {
            if (ImGui.BeginMenuBar())
            {
                if (ImGui.BeginMenu("Windows"))
                {
                    if (ImGui.MenuItem("Scene Window"))
                    {
                        sceneWindow = !sceneWindow;
                    }

                    if (ImGui.MenuItem("FileSystem window"))
                    {
                        filesystemWindow = !filesystemWindow;
                    }

                    if (ImGui.MenuItem("SceneGraph Window"))
                    {
                        sceneGraphWindow = !sceneGraphWindow;
                    }

                    if (ImGui.MenuItem("Inspector Window"))
                    {
                        inspectorWindow = !inspectorWindow;
                    }


                    ImGui.EndMenu();
                }

                ImGui.EndMenuBar();
            }

            
            if (filesystemWindow)
                RenderFilesystemWindow();
                
            if (sceneGraphWindow)
                RenderSceneGraph();

            if (sceneWindow)
                RenderSceneWindow();

            //Inspector should always render last
            if (inspectorWindow)
                RenderInspectorWindow();
        }

        void RenderSceneWindow()
        {
            ImGuiWindowFlags flags = ImGuiWindowFlags.ImGuiWindowFlags_None;
            flags |= ImGuiWindowFlags.ImGuiWindowFlags_NoCollapse;

            ImGui.Begin("Show Scene", ref sceneWindow, flags);
            ImGui.BeginGroup();

            if (ImGui.Button("Enter Play Mode"))
            {

            }
            ImGui.SameLine();

            bool docked = ImGui.IsWindowDocked();
            if (!docked && ImGui.Button("Resize To Aspect"))
            {
                Vector2 rtDims = rt.colorAttachment.GetDimensions();
                float aspect = rtDims.X / rtDims.Y;
                Vector2 windowSize = ImGui.GetWindowSize();

                if (windowSize.X > windowSize.Y)
                {
                    windowSize.Y = windowSize.X / aspect;
                }
                else
                {
                    windowSize.X = windowSize.Y * aspect;
                }

                ImGui.SetWindowSize(windowSize);
            }
            ImGui.EndGroup();

            ImGui.BeginChild("Game Render");

            Vector2 size = ImGui.GetWindowSize();
            ImGui.Image(rt.colorAttachment, size, new Vector2(0, 1), new Vector2(1, 0));
            ImGui.EndChild();

            ImGui.End();
        }

        class FooData
        {
            
        }

        string currentDir = "D:\\Dev\\Dev\\PerhapsEngine\\PerhapsEngineNative\\Build-Debug-Bin";
        int selectedIndex = -1;
        void RenderFilesystemWindow()
        {
            ImGui.Begin("FileSystem", ref filesystemWindow);
            //ImGui.Text(currentDir);
            if(ImGui.InputText("sa", ref currentDir))
            {
                Console.WriteLine(currentDir);
            }


            const int max_columns = 2;
            List<string> files = new List<string>()
            {
                    "hello.h",
                    "hello.cpp",
                    "vertex.shader",
                    "fragment.shader",
                    "shrek.png"
            };

            if(ImGui.TreeNode("FileSystem"))
            {
                ImGui.Columns(max_columns);


                for (int i = 0; i < files.Count; i++)
                {
                    ImGui.PushId(i);
                    if (ImGui.Selectable(files[i], selectedIndex == i))
                    {
                        
                        selectedIndex = i;
                        ImGui.CloseCurrentPopup();
                    }

                    if (ImGui.IsItemClicked(1))
                    {
                        ImGui.OpenPopup("file_popup");
                    }

                    if (ImGui.BeginPopup("file_popup"))
                    {
                        ImGui.MenuItem(files[i]);
                        if (ImGui.MenuItem("Rename"))
                        {

                        }

                        if (ImGui.MenuItem("Delete"))
                        {

                        }

                        ImGui.EndPopup();
                    }

                    if (ImGui.BeginDragSource())
                    {
                        ImGui.SetDragAndDropPayload("file", files[i]);
                        ImGui.Text(files[i]);
                        ImGui.EndDragAndDropSource();
                    }
                    if (ImGui.BeginDragAndDropTarget())
                    {

                        if (ImGui.AcceptDragAndDropPayload("file", out object payload))
                        {
                            Console.WriteLine($"Dropped {(string)payload} on {files[i]}");
                        }

                        ImGui.EndDragAndDropTarget();
                    }

                    ImGui.PopId();
                    ImGui.NextColumn();
                }

                ImGui.Columns(1);

                ImGui.TreePop();
            }

            ImGui.End();
        }

        void RenderInspectorWindow()
        {
            ImGui.Begin("Inspector", ref inspectorWindow);


            ImGui.End();
        }

        void RenderSceneGraph()
        {
            ImGui.Begin("Scene Graph", ref sceneGraphWindow);

            ImGui.End();
        }
    }


}
