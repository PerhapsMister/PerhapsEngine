using System;
using System.Diagnostics;
using System.Linq;
using System.Numerics;
using System.Reflection;
using System.Runtime.InteropServices;

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

            string[] args = Environment.GetCommandLineArgs();
            Console.WriteLine("Arguments: " + args.Length);

            for (int i = 0; i < args.Length; i++)
            {
                Console.WriteLine(args[i]);
            }

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

            Vector3[] poses = va.positions;
            Console.WriteLine(poses.Length);
            
            bool areEqual = Enumerable.SequenceEqual(positions, poses);
            Console.WriteLine("Equal: " + areEqual);
            Graphics.SetClearColor(new Vector4(0.5f, 0.5f, 1f, 1f));

            sw = Stopwatch.StartNew();
        }

        Stopwatch sw;
        public void OnUpdate()
        {
            Time.OnFrameStart();
            Graphics.Clear(Graphics.ClearMask.COLOR);
            Graphics.DrawVertexArray(va);
        }
    }
}
