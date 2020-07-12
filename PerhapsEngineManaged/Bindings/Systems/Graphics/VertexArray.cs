using System;
using System.Numerics;
using System.Runtime.InteropServices;

namespace Perhaps
{
    public class VertexArray : IDisposable
    {
        IntPtr mNativeObject;

        [DllImport("__Internal", EntryPoint = "CreateVertexArray")]
        static extern IntPtr MativeCreateArray();

        [DllImport("__Internal", EntryPoint = "DeleteVertexArray")]
        static extern void MativeDeleteArray(IntPtr va);

        [DllImport("__Internal", EntryPoint = "VA_SetPositions")]
        static extern void NativeSetPositions(IntPtr va, Vector2[] positions, int count);
        [DllImport("__Internal", EntryPoint = "VA_GetPositions")]
        static extern Vector2[] NativeGetPositions(IntPtr va);

        public Vector2[] positions
        {
            get
            {
                return NativeGetPositions(mNativeObject);
            }
            set
            {
                float[] pos = new float[value.Length * 2];

                for (int i = 0; i < value.Length; i++)
                {
                    pos[i] = value[i].X;
                    pos[i + 1] = value[i].Y;
                }

                NativeSetPositions(mNativeObject, value, pos.Length);
            }
        }


        public static VertexArray CreateArray()
        {
            VertexArray va = new VertexArray();
            va.mNativeObject = MativeCreateArray();

            return va;
        }

        public void Dispose()
        {
            MativeDeleteArray(mNativeObject);
            GC.SuppressFinalize(this);
        }
        private VertexArray()
        {

        }
    }
}
