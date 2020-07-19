using Perhaps.Engine;
using Perhaps.EngineEditor;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Perhaps.Engine
{
    public abstract class MonoApplication
    {
        public static MonoApplication instance { get; private set; }
        public NativeApplication nativeApp { get; private set; }


        public void Initialize(IntPtr nativeAppPtr)
        {
            Console.WriteLine($"C# dll initialized. Domain: {AppDomain.CurrentDomain.FriendlyName} " +
$"Version: {typeof(string).Assembly.ImageRuntimeVersion}");

            EngineUtils.TryExecute(() =>
            {
                Debug.Assert(instance == null, "MonoApplication instance is not null! only 1 MonoApplication may exist.");

                nativeApp = new NativeApplication(nativeAppPtr);
                //window = new Window(windowPtr);
                instance = this;

                OnInitialize();
            });    
        }

        public abstract void OnInitialize();
        public abstract void Update();
        public abstract void ShutDown();
    }
}
