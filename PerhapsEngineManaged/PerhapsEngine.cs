using System;
using System.Numerics;
using System.Runtime.InteropServices;

namespace Perhaps
{
    public class PerhapsEngine
    {
        VertexArray va;

        public void OnInitialize()
        {
            Console.WriteLine("C# dll initialized. my name is cs 461");
            va = VertexArray.CreateArray();

            Vector2[] positions = new Vector2[]
            {
                new Vector2(-0.5f, -0.5f),
                new Vector2(0.5f, -0.5f),
                new Vector2(0.5f, 0.5f),
                new Vector2(-0.5f, 0.5f)
            };

            va.positions = positions;
            for (int i = 0; i < 4; i++)
            {
                Vector2[] poses = va.positions;
            }

            /*
            Vector2[] poss = va.positions;
            Console.WriteLine(poss.Length);

            for (int i = 0; i < 4; i++)
            {
                Vector2[] poses = va.positions;
            }

            for (int i = 0; i < poss.Length; i++)
            {
                Console.WriteLine(poss[i]);
            }
            */
        }

        public void OnUpdate()
        {
            Graphics.Clear(Graphics.ClearMask.COLOR);
        }
    }
}
