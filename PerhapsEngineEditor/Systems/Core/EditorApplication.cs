using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Perhaps.Engine;

namespace Perhaps.Engine.Editor
{
    public class EditorApplication : MonoApplication
    {
        public EditorApplication(IntPtr nativeApp) : base(nativeApp)
        {
            
        }

        public override void OnInitialize()
        {
            EditorActions.Initialize();
        }

        public override void ShutDown()
        {
            
        }

        public override void Update()
        {
            
        }

        EditorRenderer editorRenderer;
        public void OnEditorGuiRender(IntPtr sceneRenderTexture)
        {
            EngineUtils.TryExecute(() =>
            {
                if (editorRenderer == null)
                {
                    editorRenderer = new EditorRenderer(sceneRenderTexture);
                }

                editorRenderer.Render();

            });
        }
    }
}
