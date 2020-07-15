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
            pathToShadersFolder = pathToShadersFolder + "\\PerhapsEngineEditor\\Shaders\\";
            Console.WriteLine(pathToShadersFolder);
            
            string vertSrc = File.ReadAllText(pathToShadersFolder + "Test.vert");
            string fragSrc = File.ReadAllText(pathToShadersFolder + "Test.frag");

            shader = Shader.CompileShader(vertSrc, fragSrc);
            shader.Bind();
            shader.SetUniformInt("val", 1);
            
            Matrix4x4 mat = Matrix4x4.Identity;
            shader.SetUniformMatrix4("model", mat);
        }
        Shader shader;

        public void OnUpdate()
        {
            try
            {
                Update();
            }
            catch(Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

        void Update()
        {
            Time.OnFrameStart();
            Graphics.Clear(Graphics.ClearMask.COLOR);
            shader.SetUniformFloat("time", Time.Elapsed);

            Matrix4x4 mat = Matrix4x4.CreateRotationZ(Time.Elapsed * MathUtils.Deg2Rad * 90f);

            shader.SetUniformMatrix4("model", mat);
            Graphics.DrawVertexArray(va);
        }
    }
}
