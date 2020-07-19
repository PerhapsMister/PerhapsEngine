using System;
using System.Numerics;
using System.Runtime.InteropServices;

namespace Perhaps.Engine
{
    public class Window
    {
        IntPtr mNativeObject;

        public Window(IntPtr nativeObject)
        {
            mNativeObject = nativeObject;
        }

        public IntPtr GetNativeObject()
        {
            return mNativeObject;
        }


        [DllImport("__Internal", EntryPoint = "Window_GetDimensions")]
        static extern Vector2 Window_GetDimensions(IntPtr window);
    }
}
