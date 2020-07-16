using Assimp;
using System.Drawing;
using System.Drawing.Imaging;
using System;
using System.IO;

namespace Perhaps.Engine
{
    public static class AssetImporter
    {
        public static Texture2D ImportTexture(string filepath)
        {
            if(!File.Exists(filepath))
            {
                Console.WriteLine($"Invalid image filepath {filepath}");
                return null;
            }
    
            Bitmap bmp = new Bitmap(filepath);
            BitmapData data = bmp.LockBits(new Rectangle(0,0, bmp.Width, bmp.Height), 
                ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);

            Texture2D tex = new Texture2D(data.Scan0, bmp.Width, bmp.Height);
            bmp.UnlockBits(data);
            
            return tex;
        }
    }
}