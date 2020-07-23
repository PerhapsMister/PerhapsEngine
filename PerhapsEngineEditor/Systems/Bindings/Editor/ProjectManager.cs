using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Newtonsoft.Json;

namespace Perhaps.Engine.Editor
{
    public static class ProjectManager
    {
        public static FileObject<PerhapsProject> CurrentProjectFile { get; private set; }
        public static PerhapsProject CurrentProject
        {
            get
            {
                if (CurrentProjectFile == null)
                    return null;

                return CurrentProjectFile.Object;
            }
        }

        public static string ErrorString { get; private set; }

        public static bool OpenProject(string filePath)
        {
            FileObject<PerhapsProject> proj = new FileObject<PerhapsProject>(filePath);

            if (proj.Load())
            {
                CurrentProjectFile = proj;
                AppendRecentProject(filePath);

                return true;
            }

            return false;
        }

        public const string projectFileExtension = ".phproject";
        public static bool CreateProject(string directoryPath, string projectTitle)
        {
            PerhapsProject proj = new PerhapsProject();
            proj.ProjectTitle = projectTitle;

            string project_path = $"{directoryPath}\\{projectTitle}{projectFileExtension}";
            FileObject<PerhapsProject> projFile = new FileObject<PerhapsProject>(project_path, proj);

            if (!projFile.Save())
            {
                Console.WriteLine("ProjectManager error: " + projFile.ErrorString);

                return false;
            }

            AppendRecentProject(project_path);

            CurrentProjectFile = projFile;
            return true;
        }

        public static string PersistentDataPath
        {
            get
            {
                string roaming = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
                string finalPath = roaming + "\\PerhapsEngine";

                if (!Directory.Exists(finalPath))
                    Directory.CreateDirectory(finalPath);

                return finalPath;
            }
        }


        static void AppendRecentProject(string path)
        {
            FileObject<RecentProjectsContainer> container = 
                new FileObject<RecentProjectsContainer>(recentProjFilePath);

            if (!container.Load())
            {
                container.Object = new RecentProjectsContainer();
            }

            container.Object.recentProjectPaths.AddFront(path);
            container.Object.recentProjectPaths = container.Object.recentProjectPaths.Distinct().ToDeque();

            container.Save();
        }


        [Serializable]
        class RecentProjectsContainer
        {
            public Deque<string> recentProjectPaths = new Deque<string>();
        }


        static string recentProjFilePath = $"{PersistentDataPath}\\RecentProjects.json";
        static FileObject<PerhapsProject>[] cachedRecentProjects;
        public static FileObject<PerhapsProject>[] GetRecentProjects()
        {
            if (cachedRecentProjects != null)
                return cachedRecentProjects;

            FileObject<RecentProjectsContainer> recentProjectsFile =
                new FileObject<RecentProjectsContainer>(recentProjFilePath);

            if (recentProjectsFile.Load())
            {
                List<FileObject<PerhapsProject>> loaded = new List<FileObject<PerhapsProject>>();
                Deque<string> paths = recentProjectsFile.Object.recentProjectPaths;

                for (int i = 0; i < paths.Count; i++)
                {
                    FileObject<PerhapsProject> file = new FileObject<PerhapsProject>(paths[i]);

                    if(file.Load())
                    {
                        loaded.Add(file);
                    }
                }

                cachedRecentProjects = loaded.ToArray();
                recentProjectsFile.Save();
            }
            else
            {
                cachedRecentProjects = new FileObject<PerhapsProject>[0];
            }

            return cachedRecentProjects;
        }
    }
}
