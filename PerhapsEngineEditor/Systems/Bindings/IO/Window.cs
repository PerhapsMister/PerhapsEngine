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

        public bool IsKeyDown(KeyCode key)
        {
            return Window_IsKeyDown(mNativeObject, key);
        }

        public bool IsKeyTapped(KeyCode key)
        {
            return Window_IsKeyTapped(mNativeObject, key);
        }

        public void SetTitle(string title)
        {
            Window_SetTitle(mNativeObject, title);
        }

        [DllImport("__Internal", EntryPoint = "Window_GetDimensions")]
        static extern void Window_GetDimensions(IntPtr window, out Vector2 dimensions);
        [DllImport("__Internal", EntryPoint = "Window_IsKeyDown")]
        static extern bool Window_IsKeyDown(IntPtr window, KeyCode key);
        [DllImport("__Internal", EntryPoint = "Window_IsKeyTapped")]
        static extern bool Window_IsKeyTapped(IntPtr window, KeyCode key);
        [DllImport("__Internal", EntryPoint = "Window_SetTitle")]
        static extern bool Window_SetTitle(IntPtr window, string title);
    }
}
