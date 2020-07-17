using System;
using System.Runtime.InteropServices;
using System.Numerics;

namespace Perhaps.Engine
{
    public class Texture2D : IDisposable
    {
        IntPtr mNativeObject;
        int mWidth, mHeight;
        #region Enums
		public enum TextureFormat
		{
			RGBA = 0x1908, RGB = 0x1907,
			DEPTH24_STENCIL8 = 0x88F0,
		};

		public enum WrapMode
		{
			CLAMP_TO_BORDER = 0x812D,
			CLAMP_TO_EDGE = 0x812F,
			REPEAT = 0x2901,
			REPEAT_MIRRORED = 0x8370
		};

		public enum FilterMode
		{
			POINT = 0x2600,
			LINEAR = 0x2601
		};
        #endregion

        public Texture2D(int width, int height)
        {
            mWidth = width;
            mHeight = height;
        }
        
        public Texture2D(IntPtr data, int width, int height)
        {
            mNativeObject = Texture2D_Create(mWidth, mHeight);
        }

        private Texture2D(IntPtr nativeObject)
        {

            mNativeObject = nativeObject;
            Vector2 dimensions = GetDimensions();
            mWidth = (int)dimensions.X;
            mHeight = (int)dimensions.Y;
        }

        public static Texture2D FromNativeObject(IntPtr nativeObject)
        {
            Texture2D tex = new Texture2D(nativeObject);
            return tex;
        }

        public static Texture2D FromNativeData(IntPtr data, int width, int height)
        {
            Texture2D tex = new Texture2D(data, width, height);
            Texture2D_LoadPixels(tex.mNativeObject, data);
            return tex;
        }

        public TextureFormat format
        {
            get
            {
                return (TextureFormat)Texture2D_GetFormat(mNativeObject);
            }
            set
            {
                Texture2D_SetFormat(mNativeObject, (int)value);
            }
        }
        public WrapMode wrapMode
        {
            get
            {
                return (WrapMode)Texture2D_GetFormat(mNativeObject);
            }
            set
            {
                Texture2D_SetFormat(mNativeObject, (int)value);
            }
        }
        public FilterMode filterMode
        {
            get
            {
                return (FilterMode)Texture2D_GetFormat(mNativeObject);
            }
            set
            {
                Texture2D_SetFormat(mNativeObject, (int)value);
            }
        }

        public void Dispose()
        {
            Texture2D_Delete(mNativeObject);
            GC.SuppressFinalize(this);
        }

        public void Apply()
        {
            if(mNativeObject == IntPtr.Zero)
            {
                mNativeObject = Texture2D_Create(mWidth, mHeight);
            }

            Texture2D_Apply(mNativeObject);
        }

        public Vector2 GetDimensions()
        {
            if(mNativeObject != IntPtr.Zero)
            {
                Texture2D_GetDimensions(mNativeObject, out Vector2 dimensions);
                return dimensions;
            }

            return new Vector2(mWidth, mHeight);
        }

        public void Bind()
        {
            Texture2D_Bind(mNativeObject);
        }

        public void Bind(int slot)
        {
            Texture2D_Bind_Slot(mNativeObject, slot);
        }

        public static void UnBind(int slot)
        {
            Texture2D_UnBind(slot);
        }

        [DllImport("__Internal", EntryPoint = "Texture2D_Create")]
        static extern IntPtr Texture2D_Create(int width, int height);
        
        [DllImport("__Internal", EntryPoint = "Texture2D_Delete")]
        static extern void Texture2D_Delete(IntPtr tex);
        [DllImport("__Internal", EntryPoint = "Texture2D_GetWrapMode")]
        static extern int Texture2D_GetWrapMode(IntPtr tex);
        [DllImport("__Internal", EntryPoint = "Texture2D_SetWrapMode")]
        static extern void Texture2D_SetWrapMode(IntPtr tex, int mode);
        [DllImport("__Internal", EntryPoint = "Texture2D_GetFilterMode")]
        static extern int Texture2D_GetFilterMode(IntPtr tex);
        [DllImport("__Internal", EntryPoint = "Texture2D_SetFilterMode")]
        static extern void Texture2D_SetFilterMode(IntPtr tex, int format);
        [DllImport("__Internal", EntryPoint = "Texture2D_GetFormat")]
        static extern int Texture2D_GetFormat(IntPtr tex);
        [DllImport("__Internal", EntryPoint = "Texture2D_SetFormat")]
        static extern void Texture2D_SetFormat(IntPtr tex, int format);
        
        [DllImport("__Internal", EntryPoint = "Texture2D_Apply")]
        static extern void Texture2D_Apply(IntPtr tex);
        
        [DllImport("__Internal", EntryPoint = "Texture2D_Bind")]
        static extern void Texture2D_Bind(IntPtr tex);
        [DllImport("__Internal", EntryPoint = "Texture2D_Bind_Slot")]
        static extern void Texture2D_Bind_Slot(IntPtr tex, int slot);
        
        [DllImport("__Internal", EntryPoint = "Texture2D_UnBind")]
        static extern void Texture2D_UnBind(int slot);
        
        [DllImport("__Internal", EntryPoint = "Texture2D_GetDimensions")]
        static extern void Texture2D_GetDimensions(IntPtr tex, out Vector2 dimensions);
        
        
    }
}