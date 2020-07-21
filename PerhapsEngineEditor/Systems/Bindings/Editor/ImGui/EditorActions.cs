using System;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;

namespace Perhaps.Engine.Editor
{
    public static class EditorActions
    {
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto, Pack = 1)]
        public struct SHFILEOPSTRUCT
        {
            public IntPtr hwnd;
            [MarshalAs(UnmanagedType.U4)] public int wFunc;
            public string pFrom;
            public string pTo;
            public short fFlags;
            [MarshalAs(UnmanagedType.Bool)] public bool fAnyOperationsAborted;
            public IntPtr hNameMappings;
            public string lpszProgressTitle;

        }

        [DllImport("shell32.dll", CharSet = CharSet.Auto)]
        static extern int SHFileOperation(ref SHFILEOPSTRUCT FileOp);
        const int FO_DELETE = 3;
        const int FOF_ALLOWUNDO = 0x40;
        const int FOF_NOCONFIRMATION = 0x10;    //Don't prompt the user.;

        public static void Initialize()
        {
            EditorRenderer.OnFileDragDropped += onFileDragDrop;
        }

        private static void onFileDragDrop(string draggedFile, string droppedFile)
        {
            Console.WriteLine($"Dropped {draggedFile} on {droppedFile}");
        }

        public static void RenameFile(string filepath, string newName)
        {
            if (!File.Exists(filepath))
                return;

            string directory = Path.GetDirectoryName(filepath);
            string newFileName = $"{directory}\\{newName}";
            Console.WriteLine($"{filepath} Renamed to {newFileName}");
            File.Move(filepath, newFileName);
        }


        public static void DeleteFile(string filepath)
        {
            if (!File.Exists(filepath))
                return;

            ThreadStart ts = new ThreadStart(() =>
            {
                SHFILEOPSTRUCT shf = new SHFILEOPSTRUCT();
                shf.wFunc = FO_DELETE;
                shf.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION;
                shf.pFrom = filepath;

                SHFileOperation(ref shf);
            });

            Thread t = new Thread(ts);
            t.Start();

        }

        public static string OpenFilePathDialog(string filter = "")
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = filter;
            if (dialog.ShowDialog() == DialogResult.OK)
                return dialog.FileName;

            return null;
        }

        public static string OpenFolderPathDialog()
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            if(dialog.ShowDialog() == DialogResult.OK)
            {
                return dialog.SelectedPath;
            }

            return null;

        }
    }
}
