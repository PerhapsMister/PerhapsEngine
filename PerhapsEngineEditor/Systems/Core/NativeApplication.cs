using Perhaps.Engine;
using System;
using System.Runtime.InteropServices;

namespace Perhaps.EngineEditor
{
    public class NativeApplication
    {
        IntPtr mNativeObject;
        public Window window { get; private set; }

        public NativeApplication(IntPtr app)
        {
            mNativeObject = app;

            IntPtr windowPtr = App_GetWindow(app);
            window = new Window(windowPtr);
        }

        public IntPtr GetNativeObject()
        {
            return mNativeObject;
        }

        [DllImport("__Internal", EntryPoint = "App_GetWindow")]
        public static extern IntPtr App_GetWindow(IntPtr app);
    }
}
