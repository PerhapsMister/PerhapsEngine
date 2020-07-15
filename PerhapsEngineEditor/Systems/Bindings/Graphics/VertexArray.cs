using System;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Linq;

namespace Perhaps.Engine
{
    public class VertexArray : IDisposable
    {
        IntPtr mNativeObject;

        public IntPtr GetNativeObject()
        {
            return mNativeObject;
        }

        public Vector3[] positions
        {
            get
            {
                VA_GetPositions(mNativeObject, out IntPtr positions, out int count);

                float[] floats = new float[count];
                Marshal.Copy(positions, floats, 0, count);
                
                Vector3[] vectors = new Vector3[count/3];
                for (int i = 0; i < floats.Length; i+=3)
                {
                    int index = i / 3;
                    vectors[index].X = floats[i];
                    vectors[index].Y = floats[i+1];
                    vectors[index].Z = floats[i+2];
                }

                return vectors;
            }
            set
            {
                float[] pos = new float[value.Length * 3];

                for (int i = 0; i < value.Length; i++)
                {
                    pos[i] = value[i].X;
                    pos[i + 1] = value[i].Y;
                    pos[i + 2] = value[i].Z;
                }

                VA_SetPositions(mNativeObject, value, pos.Length);
            }
        }

        public uint[] Indices
        {
            get
            {
                VA_GetIndices(mNativeObject, out IntPtr indices, out int count);
                int[] dest = new int[count];
                Marshal.Copy(indices, dest, 0, count);

                return dest.OfType<uint>().ToArray();
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
        [DllImport("__Internal", EntryPoint = "VA_SetPositions")]
        static extern void VA_SetPositions(IntPtr va, Vector3[] positions, int count);
        [DllImport("__Internal", EntryPoint = "VA_GetPositions")]
        static extern void VA_GetPositions(IntPtr va, out IntPtr positions, out int count);
        [DllImport("__Internal", EntryPoint = "VA_Upload")]
        static extern void VA_Upload(IntPtr va);
        [DllImport("__Internal", EntryPoint = "VA_Bind")]
        static extern bool VA_Bind(IntPtr va);
        [DllImport("__Internal", EntryPoint = "VA_Unbind")]
        static extern void VA_Unbind();

        [DllImport("__Internal", EntryPoint = "VA_GetIndices")]
        static extern void VA_GetIndices(IntPtr va, out IntPtr indices, out int count);

        [DllImport("__Internal", EntryPoint = "VA_SetIndices")]
        static extern void VA_SetIndices(IntPtr va, uint[] indices, int count);
    }
}
