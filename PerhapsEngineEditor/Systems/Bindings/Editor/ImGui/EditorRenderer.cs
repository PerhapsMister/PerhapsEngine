using System;
using System.Runtime.InteropServices;
using System.Numerics;
using System.Collections.Generic;
using System.IO;
using System.Linq;

using System.Windows;
using System.Windows.Forms;
using Perhaps.Engine.Editor;

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
        bool projectPanelWindow = true;

        public void Render()
        {
            RenderProject();
        }

        void RenderProject()
        {
            if(MonoApplication.instance.nativeApp.window.IsKeyTapped(KeyCode.E))
            {
                Console.WriteLine(ProjectManager.PersistentDataPath);
            }

            if (ImGui.BeginMenuBar())
            {
                if (ImGui.BeginMenu("Windows"))
                {
                    if (ImGui.MenuItem("Project Window"))
                    {
                        projectPanelWindow = !projectPanelWindow;
                    }

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

            if (projectPanelWindow)
                RenderProjectWindow();

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

        const string defaultTitle = "A New Project";
        string projectTitle = defaultTitle;
        void RenderProjectWindow()
        {
            ImGui.Begin("Project",ref projectPanelWindow);
            if(ProjectManager.CurrentProject == null)
            {
                RenderProjectLoadPanel();

                if(ProjectManager.CurrentProject != null)
                {
                    fileSystemBrowsedDirectory = ProjectManager.CurrentProject.ProjectDirectory;
                }
            }
            else
            {
                RenderOngoingProject();
            }

            ImGui.End();
        }

        void RenderProjectLoadPanel()
        {
            ImGui.BulletText("New projects must be placed in an empty directory.");

            ImGui.Text("Project Title:");
            ImGui.SameLine();
            ImGui.InputText("##label", ref projectTitle);

            if (ImGui.Button("Create New"))
            {
                string path = EditorActions.OpenFolderPathDialog();
                if (path != null)
                {
                    if (!ProjectManager.CreateProject(path, projectTitle))
                    {
                        Console.WriteLine("ProjectManager error: " + ProjectManager.ErrorString);
                    }

                    projectTitle = defaultTitle;
                }
            }

            ImGui.Separator();
            if (ImGui.Button("Load Existing"))
            {
                string path = EditorActions.OpenFilePathDialog("Perhaps Project Files (*.phproject)|*.phproject");
                if (path != null)
                {
                    if (!ProjectManager.OpenProject(path))
                    {
                        Console.WriteLine("ProjectManager error: " + ProjectManager.ErrorString);
                    }

                    projectTitle = defaultTitle;
                }
            }

            ImGui.Separator();
            ImGui.BulletText("Recent Projects:");

            PerhapsProject[] projects = ProjectManager.GetRecentProjects();
            ImGui.Separator();
            for (int i = 0; i < projects.Length; i++)
            {
                PerhapsProject project = projects[i];

                ImGui.PushItemWidth(-1);
                if (ImGui.Button($"{project.ProjectTitle}\n{project.ProjectPath}\nTime Created: {project.timeCreated.ToString()}"))
                {
                    ProjectManager.OpenProject(project.ProjectPath);
                    break;
                }
                ImGui.PopItemWidth();

                ImGui.Separator();
            }

        }

        void RenderOngoingProject()
        {
            ImGui.BulletText("Project Name:");
            ImGui.SameLine();
            ImGui.Text(ProjectManager.CurrentProject.ProjectTitle);
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

        string fileSystemBrowsedDirectory;
        int selectedIndex = -1;
        bool pathHasChanged = true;
        void RenderFilesystemWindow()
        {
            ImGui.Begin("FileSystem", ref filesystemWindow);
            //ImGui.Text(currentDir);

            ImGui.PushItemWidth(-1);
            if (ImGui.InputText("dirInput", ref fileSystemBrowsedDirectory))
            {

            }

            ImGui.PopItemWidth();
            RenderDirectoryRecursive(fileSystemBrowsedDirectory, true);


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

        static string renameFileText;
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
                ImGui.BulletText(fileName);

                bool renameChosen = false;
                if (ImGui.MenuItem("Rename"))
                {
                    renameFileText = fileName;
                    renameChosen = true;
                }

                if (ImGui.MenuItem("Delete"))
                {
                    EditorActions.DeleteFile(fullPath);
                }

                ImGui.EndPopup();

                if (renameChosen)
                {
                    ImGui.CloseCurrentPopup();
                    ImGui.OpenPopup("renamepop");
                }
            }

            if (ImGui.BeginPopup("renamepop"))
            {
                ImGui.BulletText("Rename:");
                ImGui.Separator();
                ImGui.InputText("##label", ref renameFileText);

                if (MonoApplication.instance.nativeApp.window.IsKeyTapped(KeyCode.Enter))
                {
                    EditorActions.RenameFile(fullPath, renameFileText);
                    ImGui.CloseCurrentPopup();
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
