using System;
using System.Runtime.InteropServices;

namespace Perhaps.Engine
{
    public class RenderTexture
    {
        IntPtr mNativeObject;

        public static RenderTexture CreateRenderTexture(int width, int height)
        {
            RenderTexture rt = new RenderTexture();
            rt.mNativeObject = RenderTexture_Create(width, height);

            return rt;
        }
        private RenderTexture(){}

        public void Bind()
        {
            RenderTexture_Bind(mNativeObject);
        }

        public static void Unbind()
        {
            RenderTexture_UnBind();
        }

        public void AttachColorTexture()
        {
            RenderTexture_AttachColorTexture(mNativeObject);
        }

        public void AttachDepthStencilBuffer()
        {
            RenderTexture_AttachDepthStencilBuffer(mNativeObject);
        }

        Texture2D mTex;
        public Texture2D colorAttachment
        {
            get
            {
                if(mTex == null)
                {
                    IntPtr colorTex = RenderTexture_GetColorAttachment(mNativeObject);
                    mTex = Texture2D.FromNativeObject(colorTex);
                }

                return mTex;
            }
        }


        [DllImport("__Internal", EntryPoint = "RenderTexture_Create")]
        static extern IntPtr RenderTexture_Create(int width, int height);
        [DllImport("__Internal", EntryPoint = "RenderTexture_Delete")]
        static extern void RenderTexture_Delete(IntPtr rt);
        [DllImport("__Internal", EntryPoint = "RenderTexture_Bind")]
        static extern bool RenderTexture_Bind(IntPtr rt);
        [DllImport("__Internal", EntryPoint = "RenderTexture_UnBind")]
        static extern void RenderTexture_UnBind();
        [DllImport("__Internal", EntryPoint = "RenderTexture_AttachColorTexture")]
        static extern void RenderTexture_AttachColorTexture(IntPtr rt);
        [DllImport("__Internal", EntryPoint = "RenderTexture_AttachDepthStencilBuffer")]
        static extern void RenderTexture_AttachDepthStencilBuffer(IntPtr rt);
        [DllImport("__Internal", EntryPoint = "RenderTexture_GetColorAttachment")]
        static extern IntPtr RenderTexture_GetColorAttachment(IntPtr tex);
    }
}