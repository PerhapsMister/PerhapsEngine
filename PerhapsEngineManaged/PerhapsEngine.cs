using System;
using System.Runtime.InteropServices;

namespace Perhaps
{
    public class PerhapsEngine
    {
        public void OnInitialize()
        {
            Console.WriteLine("C# dll initialized. my name is cs 461");
        }

        [DllImport("__Internal", EntryPoint = "DoSomething")]
        extern public static void DoSomething();

        public void OnUpdate()
        {
            //DoSomething();
            //Graphics.Clear(Graphics.ClearMask.COLOR);
            //Graphics.Clear(Graphics.ClearMask.COLOR);
        }
    }
}
