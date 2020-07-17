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
        
        const string screenQuadVs = @"
            #version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;

out vec2 uv;
void main()
{
    gl_Position =  vec4(aPos, 1.0);
    uv = aUv;
}
        ";

        const string screenQuadFs = @"
            #version 430 core
            out vec4 FragColor;
            in vec2 uv;
            uniform sampler2D tex;

            void main()
            {
                vec4 color = texture(tex, uv);
                FragColor = color;
            }

        ";

        RenderTexture rt;
        VertexArray va;
        Shader checkerShader, fullScreenQuadShader;
        void Init()
        {
            Console.WriteLine($"C# dll initialized. Domain: {AppDomain.CurrentDomain.FriendlyName} Version: {typeof(string).Assembly.ImageRuntimeVersion}");
            /*
            va = VertexArray.CreateArray();

/*
            Vector3[] pos = new Vector3[]
            {
                new Vector3(-1f, 1f, 0f),//top left
                new Vector3(1f, -1f, 0f),//bottom right
                new Vector3(1f, 1f, 0f),//top right
                new Vector3(-1f, -1f, 0f),//bottom left
            };
            
            Vector3[] pos = new Vector3[]
            {
                new Vector3(-0.5f, 0.5f, 0f),//top left
                new Vector3(0.5f, -0.5f, 0f),//bottom right
                new Vector3(0.5f, 0.5f, 0f),//top right
                new Vector3(-0.5f, -0.5f, 0f),//bottom left
            };

            Vector2[] uvs = new Vector2[]
            {
                new Vector2(0,1),
                new Vector2(1,0),
                new Vector2(1,1),
                new Vector2(0,0),
            };

            int[] indices = new int[]
            {
                3,1,0, //bottom left bottom right top left
                1,2,0//bottom right top right top left
            };

            va.vertices = GraphicsUtils.ToVertices(pos, uvs);
            va.indices = indices;
            va.UploadData();
            va.Bind();


            string shaderFolderPath = "D:\\Dev\\Dev\\PerhapsEngine\\PerhapsEngineEditor\\Shaders\\";
            string  vertShader = File.ReadAllText(shaderFolderPath + "Test.vert");
            string  fragShader = File.ReadAllText(shaderFolderPath + "Test.frag");
            checkerShader = Shader.CompileShader(vertShader, fragShader);
            checkerShader.Bind();

            const int width = 1280, height = 720;
            const float factor = 1f;
            rt = RenderTexture.CreateRenderTexture((int)(width * factor), (int)(height * factor));
            rt.AttachColorTexture();
            rt.AttachDepthStencilBuffer();
            RenderTexture.Unbind();

            fullScreenQuadShader = Shader.CompileShader(screenQuadVs,screenQuadFs);

            texture = AssetImporter.ImportTexture("D:\\Dev\\Dev\\PerhapsEngine\\PerhapsEngineEditor\\Images\\shrek.jpg");
            */
        }

        Texture2D texture;

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
            /*
            Graphics.SetClearColor(new Vector4(0.5f, 0.5f, 1f, 1f));
            Graphics.Clear(Graphics.ClearMask.COLOR_DEPTH_STENCIL);
            
            //rt.Bind();
            Graphics.Enable(Graphics.EnableParam.DEPTH_TEST, true);
            Graphics.SetClearColor(new Vector4(1, 0,0, 1));

            fullScreenQuadShader.Bind();
            texture.Bind(0);  
            fullScreenQuadShader.SetUniformInt("tex", 0);
            va.Bind();
            Graphics.DrawVertexArray(va);        
            //RenderTexture.Unbind();


            /*
            Graphics.Enable(Graphics.EnableParam.DEPTH_TEST, false);

            fullScreenQuadShader.Bind();
            rt.colorAttachment.Bind(1);
            fullScreenQuadShader.SetUniformInt("tex", 1);
            Graphics.DrawVertexArray(va);
            */

        }
    }
}
