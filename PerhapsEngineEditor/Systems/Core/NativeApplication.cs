using Perhaps.Engine;
using System;

namespace Perhaps.EngineEditor
{
    public class NativeApplication
    {
        IntPtr mNativeObject;
        public Window window { get; private set; }

        public NativeApplication(IntPtr app)
        {
            mNativeObject = app;
        }

        public IntPtr GetNativeObject()
        {
            return mNativeObject;
        }

    }
}
