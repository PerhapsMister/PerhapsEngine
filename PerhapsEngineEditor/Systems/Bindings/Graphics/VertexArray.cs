using System;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Linq;

namespace Perhaps.Engine
{
    [System.Serializable]
    [StructLayout(LayoutKind.Explicit)]
    public struct Vertex
    {
        [FieldOffset(0)]
        public Vector3 position;
        [FieldOffset(3 * 4)]
		public Vector2 uv;
        [FieldOffset(5 * 4)]
		public Vector3 normal;
    }

    public class VertexArray : IDisposable
    {
        IntPtr mNativeObject;

        public IntPtr GetNativeObject()
        {
            return mNativeObject;
        }


        public Vertex[] vertices
        {
            get
            {
                VA_GetVertices(mNativeObject, out IntPtr verticesLocation, out int count);

                byte[] vertBytes = new byte[Marshal.SizeOf(typeof(Vertex)) * count];
                Marshal.Copy(verticesLocation, vertBytes, 0, vertBytes.Length);
                Span<Vertex> vertices = MemoryMarshal.Cast<byte, Vertex>(vertBytes.AsSpan());

                Vertex[] verts = vertices.ToArray();
                return verts;
            }
            set
            {
                VA_SetVertices(mNativeObject, value, value.Length);
            }
        }
        
        public int[] indices
        {
            get
            {
                VA_GetIndices(mNativeObject, out IntPtr indices, out int count);
                int[] dest = new int[count];
                Marshal.Copy(indices, dest, 0, count);

                return dest;
            }
            set
            {
                VA_SetIndices(mNativeObject, value, value.Length);
            }
        }


        public static VertexArray CreateArray()
        {
            VertexArray va = new VertexArray();
            va.mNativeObject = VA_Create();

            return va;
        }

        public bool Bind()
        {
            return VA_Bind(mNativeObject);
        }

        public static void Unbind()
        {
            VA_Unbind();
        }

        public void UploadData()
        {
            VA_Upload(mNativeObject);
        }

        public void Dispose()
        {
            VA_Delete(mNativeObject);
            GC.SuppressFinalize(this);
        }
        private VertexArray()
        {

        }
        
        [DllImport("__Internal", EntryPoint = "VA_Create")]
        static extern IntPtr VA_Create();
        [DllImport("__Internal", EntryPoint = "VA_Delete")]
        static extern void VA_Delete(IntPtr va);
        [DllImport("__Internal", EntryPoint = "VA_SetVertices")]
        static extern void VA_SetVertices(IntPtr va, Vertex[] vertices, int count);
        [DllImport("__Internal", EntryPoint = "VA_GetVertices")]
        static extern void VA_GetVertices(IntPtr va, out IntPtr vertices, out int count);

        [DllImport("__Internal", EntryPoint = "VA_Upload")]
        static extern void VA_Upload(IntPtr va);
        [DllImport("__Internal", EntryPoint = "VA_Bind")]
        static extern bool VA_Bind(IntPtr va);
        [DllImport("__Internal", EntryPoint = "VA_Unbind")]
        static extern void VA_Unbind();

        [DllImport("__Internal", EntryPoint = "VA_GetIndices")]
        static extern void VA_GetIndices(IntPtr va, out IntPtr indices, out int count);

        [DllImport("__Internal", EntryPoint = "VA_SetIndices")]
        static extern void VA_SetIndices(IntPtr va, int[] indices, int count);
    }
}
