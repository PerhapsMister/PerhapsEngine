using System;
using System.IO;
using System.Runtime.InteropServices;

namespace Perhaps.Engine
{
    public class Shader : IDisposable
    {
        private IntPtr mNativeObject;
        public IntPtr GetNativeObject()
        {
            return mNativeObject;
        }

        public void Dispose()
        {
            Shader_Delete(mNativeObject);
            GC.SuppressFinalize(this);
        }

        public void Bind()
        {
            Shader_Bind(mNativeObject);
        }

        public static void Unbind()
        {
            Shader_Unbind();
        }

        public bool Bound => Shader_IsBound(mNativeObject);

        public static Shader CompileShader(string vertexSrc, string fragmentSrc)
        {
            IntPtr nativeShader = Shader_CompileShader(vertexSrc, fragmentSrc);
            if(nativeShader == IntPtr.Zero)
                return null;
            
            return new Shader() { mNativeObject = nativeShader };
        }

        Shader()
        {

        }

        
        [DllImport("__Internal", EntryPoint = "Shader_CompileShader")]
        static extern IntPtr Shader_CompileShader(string vertSrc, string fragSrc);
        [DllImport("__Internal", EntryPoint = "Shader_Delete")]
        static extern void Shader_Delete(IntPtr nativeShader);

        [DllImport("__Internal", EntryPoint = "Shader_Bind")]
        static extern void Shader_Bind(IntPtr nativeShader);

        [DllImport("__Internal", EntryPoint = "Shader_Unbind")]
        static extern void Shader_Unbind();

        [DllImport("__Internal", EntryPoint = "Shader_IsBound")]
        static extern bool Shader_IsBound(IntPtr nativeShader);
    }
}