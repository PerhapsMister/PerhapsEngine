using System;
using System.Runtime.InteropServices;

namespace Perhaps
{
    public static class Graphics
    {
        public enum ClearMask
        {
            COLOR = 0x00004000, DEPTH = 0x00000100, STENCIL = 0x00000400,
            COLOR_DEPTH = (int)COLOR | (int)DEPTH, COLOR_STENCIL = (int)COLOR | (int)STENCIL,
            COLOR_DEPTH_STENCIL = (int)COLOR | (int)DEPTH | (int)STENCIL
        };

        [DllImport("__Internal", EntryPoint = "Clear")]
        public static extern void Clear(ClearMask mask);

    }
}
