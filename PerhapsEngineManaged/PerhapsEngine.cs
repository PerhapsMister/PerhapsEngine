using System;
using System.Diagnostics;
using System.Linq;
using System.Numerics;
using System.Reflection;
using System.Runtime.InteropServices;
using System.IO;

namespace Perhaps.Engine
{
    public class PerhapsEngine
    {
        VertexArray va;
        public void OnInitialize()
        {
            try
            {
                Init();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }

        }
        
        void Init()
        {
            Console.WriteLine($"C# dll initialized. Domain: {AppDomain.CurrentDomain.FriendlyName} Version: {typeof(string).Assembly.ImageRuntimeVersion}");
            va = VertexArray.CreateArray();

            Vector3[] positions = new Vector3[]
            {
                new Vector3(-0.5f, -0.5f, 0f),//bottom left
                new Vector3(0.5f, -0.5f, 0f),//bottom right
                new Vector3(0.5f, 0.5f, 0f),//top right
                new Vector3(-0.5f, 0.5f, 0f)//top left
            };

            va.positions = positions;
            va.Indices = new uint[]
            {
                0,1,3,
                1,2,3
            };
            va.UploadData();
            va.Bind();

            Graphics.SetClearColor(new Vector4(0.5f, 0.5f, 1f, 1f));

            string pathToShadersFolder= Environment.CurrentDirectory;
            pathToShadersFolder = Path.GetFullPath(Path.Combine(pathToShadersFolder, @"..\"));
            pathToShadersFolder = pathToShadersFolder + "\\PerhapsEngineManaged\\Shaders\\";
            Console.WriteLine(pathToShadersFolder);
            
            string vertSrc = File.ReadAllText(pathToShadersFolder + "Test.vert");
            string fragSrc = File.ReadAllText(pathToShadersFolder + "Test.frag");

            Shader h = Shader.CompileShader(vertSrc, fragSrc);
            Console.WriteLine("Shader compiled: " + (h != null));
            h.Bind();
            
        }

        public void OnUpdate()
        {
            Time.OnFrameStart();
            Graphics.Clear(Graphics.ClearMask.COLOR);
            Graphics.DrawVertexArray(va);
        }
    }
}
