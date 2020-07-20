using System;
using System.Runtime.InteropServices;
using System.Numerics;
using System.Collections.Generic;
using System.IO;
using System.Linq;

using System.Windows;
using System.Windows.Forms;

namespace Perhaps.Engine
{
    /// <summary>
    /// In charge of rendering the editor.
    /// </summary>
    public class EditorRenderer
    {
        public static event Action<string, string> OnFileDragDropped;

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
        bool pathHasChanged = true;
        void RenderFilesystemWindow()
        {
            ImGui.Begin("FileSystem", ref filesystemWindow);
            //ImGui.Text(currentDir);

            ImGui.PushItemWidth(-1);
            if (ImGui.InputText("dirInput", ref currentDir))
            {

            }

            ImGui.PopItemWidth();
            RenderDirectoryRecursive(currentDir, true);


            ImGui.End();
        }

        void RenderDirectoryRecursive(string path, bool firstRecurring = false)
        {
            if (!Directory.Exists(path))
            {
                ImGui.Text("Directory path invalid.");
                return;
            }

            string[] files = Directory.GetDirectories(path);
            int directoryCount = files.Length;
            files = files.Concat(Directory.GetFiles(path)).ToArray();

            const int max_columns = 1;
            if (firstRecurring)
                ImGui.Columns(max_columns);

            for (int i = 0; i < files.Length; i++)
            {
                bool isDirectory = i < directoryCount;
                string fullPath = files[i];
                string fileName = files[i];

                int last = files[i].LastIndexOf(Path.DirectorySeparatorChar) + 1;
                if (last > 1)
                {
                    fileName = files[i].Substring(last, files[i].Length - last);
                }


                if (isDirectory)
                {
                    RenderSubDirectory(fileName, fullPath, i);
                }
                else
                {
                    RenderFile(fileName, fullPath, i);
                }

                ImGui.NextColumn();
            }

            if (firstRecurring)
                ImGui.Columns(1);

        }

        void RenderSubDirectory(string fileName, string fullPath, int index)
        {

            ImGui.Bullet();
            ImGui.SameLine();
            if (ImGui.TreeNode(fileName))
            {
                RenderDirectoryRecursive(fullPath);

                ImGui.PopTree();
            }
        }

        void RenderFile(string fileName, string fullPath, int index)
        {
            ImGui.PushId(fileName);

            if (ImGui.Selectable(fileName, selectedIndex == index))
            {
                selectedIndex = index;
                ImGui.CloseCurrentPopup();
            }

            if (ImGui.IsItemClicked(1))
            {
                ImGui.OpenPopup("file_popup");
            }
            if (ImGui.BeginPopup("file_popup"))
            {
                ImGui.MenuItem(fileName);
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
                ImGui.SetDragAndDropPayload("file", fullPath);

                ImGui.Text(fileName);
                ImGui.EndDragAndDropSource();
            }
            if (ImGui.BeginDragAndDropTarget())
            {
                if (ImGui.AcceptDragAndDropPayload("file", out object payload))
                {
                    string draggedFile = (string)payload;

                    if (OnFileDragDropped != null)
                    {
                        OnFileDragDropped(draggedFile, fullPath);
                    }
                }
                ImGui.EndDragAndDropTarget();
            }
            ImGui.PopId();
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
