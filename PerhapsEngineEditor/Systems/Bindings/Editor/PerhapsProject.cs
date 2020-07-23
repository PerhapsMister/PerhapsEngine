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
        public DateTime timeCreated { get; private set; }

        public PerhapsProject()
        {
            projectGuid = Guid.NewGuid();
            ProjectTitle = "A Perhaps Project.";
            timeCreated = DateTime.Now;
        }
    }
}
