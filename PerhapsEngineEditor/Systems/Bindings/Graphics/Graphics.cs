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
        public enum EnableParam
		{
			DEPTH_TEST = 0x0B71,
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
        
        public static void Enable(EnableParam param, bool value)
        {
            Graphics_Enable((int)param,value);
        }

        [DllImport("__Internal", EntryPoint = "Graphics_Clear")]
        static extern void Graphics_Clear(ClearMask mask);

        [DllImport("__Internal", EntryPoint = "Graphics_SetClearColor")]
        static extern void Graphics_SetClearColor(Vector4 color);

        [DllImport("__Internal", EntryPoint = "Graphics_Draw")]
        static extern void Graphics_Draw(IntPtr va);
        [DllImport("__Internal", EntryPoint = "Graphics_Enable")]
        static extern void Graphics_Enable(int param, bool value);

    }
}
