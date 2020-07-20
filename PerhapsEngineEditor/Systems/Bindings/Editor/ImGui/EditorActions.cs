using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Perhaps.Engine.Editor
{
    public static class EditorActions
    {
        public static void Initialize()
        {
            EditorRenderer.OnFileDragDropped += onFileDragDrop;
        }

        private static void onFileDragDrop(string draggedFile, string droppedFile)
        {
            Console.WriteLine($"Dropped {draggedFile} on {droppedFile}");
        }
    }
}
