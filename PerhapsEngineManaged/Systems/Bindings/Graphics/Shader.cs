using System;
using System.IO;

namespace Perhaps.Engine
{
    public class Shader : IDisposable
    {
        private IntPtr nativeObject;
        public IntPtr GetNativeObject()
        {
            return nativeObject;
        }

        public void Dispose()
        {
            GC.SuppressFinalize(this);
        }

        public Shader(string vertexSrc, string fragmentSrc)
        {
            
        }
    }
}