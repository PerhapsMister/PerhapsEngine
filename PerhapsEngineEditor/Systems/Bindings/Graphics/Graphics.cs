using System;
using System.Drawing;
using System.Numerics;
using System.Runtime.InteropServices;

namespace Perhaps.Engine
{
    public static class Graphics
    {
        public enum ClearMask
        {
            COLOR = 0x00004000, DEPTH = 0x00000100, STENCIL = 0x00000400,
            COLOR_DEPTH = (int)COLOR | (int)DEPTH, COLOR_STENCIL = (int)COLOR | (int)STENCIL,
            COLOR_DEPTH_STENCIL = (int)COLOR | (int)DEPTH | (int)STENCIL
        };

        public static void DrawVertexArray(VertexArray va)
        {
            Graphics_Draw(va.GetNativeObject());
        }

        public static void Clear(ClearMask mask)
        {
            Graphics_Clear(mask);
        }

        public static void SetClearColor(Vector4 color)
        {
            Graphics_SetClearColor(color);
        }

        [DllImport("__Internal", EntryPoint = "Graphics_Clear")]
        static extern void Graphics_Clear(ClearMask mask);

        [DllImport("__Internal", EntryPoint = "Graphics_SetClearColor")]
        static extern void Graphics_SetClearColor(Vector4 color);

        [DllImport("__Internal", EntryPoint = "Graphics_Draw")]
        static extern void Graphics_Draw(IntPtr va);

    }
}
