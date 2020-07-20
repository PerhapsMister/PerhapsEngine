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

        public Vector2 GetDimensions()
        {
            Window_GetDimensions(mNativeObject, out Vector2 dimensions);
            return dimensions;
        }


        [DllImport("__Internal", EntryPoint = "Window_GetDimensions")]
        static extern void Window_GetDimensions(IntPtr window, out Vector2 dimensions);
    }
}
