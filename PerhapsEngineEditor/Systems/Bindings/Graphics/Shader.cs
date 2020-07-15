using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Numerics;

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

        public void SetUniformInt(string name, int value)
        {
            Shader_SetInt(mNativeObject, name, value);
        }

        public void SetUniformFloat(string name, float value)
        {
            Shader_SetFloat(mNativeObject, name, value);
        }

        public void SetUniformMatrix4(string name, Matrix4x4 matrix)
        {
            Shader_SetMatrix4(mNativeObject, name, matrix);
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
        [DllImport("__Internal", EntryPoint = "Shader_SetInt")]
        static extern bool Shader_SetInt(IntPtr nativeShader, string uniformName, int value);
        [DllImport("__Internal", EntryPoint = "Shader_SetFloat")]
        static extern bool Shader_SetFloat(IntPtr nativeShader, string uniformName, float value);
        [DllImport("__Internal", EntryPoint = "Shader_SetMatrix4")]
        static extern bool Shader_SetMatrix4(IntPtr nativeShader, string uniformName, Matrix4x4 value);
        
    }
}