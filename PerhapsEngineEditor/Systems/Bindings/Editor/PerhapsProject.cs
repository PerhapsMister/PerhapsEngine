using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Perhaps.Engine.Editor
{
    [System.Serializable]
    public class PerhapsProject
    {
        public Guid projectGuid { get; private set; }
        public string ProjectTitle { get; set; }
        public string ProjectPath { get; private set; }

        [JsonIgnore]
        public string ProjectDirectory
        {
            get
            {
                int last = ProjectPath.LastIndexOf("\\");
                return ProjectPath.Substring(0, last);
            }
        }

        public DateTime timeCreated { get; private set; }

        public PerhapsProject(string projectPath)
        {
            projectGuid = Guid.NewGuid();
            ProjectTitle = "A Perhaps Project.";
            ProjectPath = projectPath;
            timeCreated = DateTime.Now;
        }

        public void Save()
        {
            string jsonString = JsonConvert.SerializeObject(this);
            File.WriteAllText(ProjectPath, jsonString);
        }

    }
}
