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

        void Init()
        {

        }

        public void OnUpdate()
        {
            try
            {
                Update();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

        void Update()
        {
            Time.OnFrameStart();
        }

		EditorRenderer editorRenderer;
        public void OnEditorRender(IntPtr renderTexture)
        {
            try
            {
				if (editorRenderer == null)
					editorRenderer = new EditorRenderer(renderTexture);

				editorRenderer.Render();
            }
            catch(Exception e)
            {
                Console.WriteLine(e.ToString());
            }

        }
	}
}
