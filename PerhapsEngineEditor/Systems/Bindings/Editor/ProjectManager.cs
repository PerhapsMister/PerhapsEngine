using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Newtonsoft.Json;

namespace Perhaps.Engine.Editor
{
    public static class ProjectManager
    {
        public static PerhapsProject CurrentProject { get; private set; }

        public static string ErrorString { get; private set; }

        public static bool OpenProject(string filePath)
        {
            if (!File.Exists(filePath))
            {
                ErrorString = $"Invalid filepath {filePath}";
                return false;
            }

            PerhapsProject project = LoadProject(filePath);
            if (project == null)
            {
                ErrorString = $"Failed to parse file {filePath}";
                return false;
            }
            CurrentProject = project;
            AppendRecentProject(filePath);

            return true;
        }

        public static bool CreateProject(string directoryPath, string projectTitle)
        {
            if (!Directory.Exists(directoryPath))
            {
                ErrorString = $"Directory invalid: {directoryPath}";
                return false;
            }
            string projectPath = $"{directoryPath}\\{projectTitle}.phproject";

            PerhapsProject project = new PerhapsProject(projectPath);
            project.ProjectTitle = projectTitle;

            Console.WriteLine(project.ProjectDirectory);

            project.Save();
            CurrentProject = project;
            AppendRecentProject(projectPath);

            return true;
        }

        static PerhapsProject LoadProject(string path)
        {
            if (!File.Exists(path))
                return null;

            string jsonProj = File.ReadAllText(path);
            PerhapsProject project = JsonConvert.DeserializeObject<PerhapsProject>(jsonProj);
            return project;
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

        [System.Serializable]
        class RecentProjects
        {
            public Deque<string> recentProjectPaths = new Deque<string>();
        }

        static void AppendRecentProject(string path)
        {
            string recentProjFile = $"{PersistentDataPath}\\RecentProjects.json";

            RecentProjects recent = new RecentProjects();
            if (File.Exists(recentProjFile))
            {
                string jsonStr = File.ReadAllText(recentProjFile);
                recent = JsonConvert.DeserializeObject<RecentProjects>(jsonStr);
            }

            if(recent.recentProjectPaths.Contains(path))
            {
                recent.recentProjectPaths.Remove(path);
            }
            recent.recentProjectPaths.AddFront(path);

            string str = JsonConvert.SerializeObject(recent);
            File.WriteAllText(recentProjFile, str);
            recentProjects = null;
        }


        static PerhapsProject[] recentProjects;
        public static PerhapsProject[] GetRecentProjects()
        {
            if (recentProjects != null)
                return recentProjects;

            string recentProjFile = $"{PersistentDataPath}\\RecentProjects.json";
            if (!File.Exists(recentProjFile))
            {
                recentProjects = new PerhapsProject[0];
                return recentProjects;
            }

            string recentJson = File.ReadAllText(recentProjFile);
            RecentProjects projs = JsonConvert.DeserializeObject<RecentProjects>(recentJson);
            if (projs == null)
            {
                recentProjects = new PerhapsProject[0];
            }
            else
            {
                List<PerhapsProject> recentProjectsList = new List<PerhapsProject>();
                List<string> pathsToCleanup = new List<string>();
                for (int i = 0; i < projs.recentProjectPaths.Count; i++)
                {
                    PerhapsProject proj = LoadProject(projs.recentProjectPaths[i]);
                    if (proj == null)
                    {
                        pathsToCleanup.Add(projs.recentProjectPaths[i]);
                        continue;
                    }
                    recentProjectsList.Add(proj);
                }

                recentProjects = recentProjectsList.ToArray();
            }

            return recentProjects;
        }
    }
}
