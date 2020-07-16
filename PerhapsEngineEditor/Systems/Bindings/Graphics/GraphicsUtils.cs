using System;
using System.Numerics;

namespace Perhaps.Engine
{
    public static class GraphicsUtils
    {
        public static Vertex[] ToVertices(Vector3[] positions)
        {
            Vertex[] vertices = new Vertex[positions.Length];

            for (int i = 0; i < positions.Length; i++)
            {
                vertices[i].position = positions[i];
            }

            return vertices;
        }

        public static Vertex[] ToVertices(Vector3[] positions, Vector2[] uvs)
        {
            if(positions.Length != uvs.Length)
            {
                Console.WriteLine("position and uv lengths are not equal");
                return null;
            }

            Vertex[] vertices = ToVertices(positions);
            for (int i = 0; i < vertices.Length; i++)
            {
                vertices[i].uv = uvs[i];
            }

            return vertices;
        }

        public static Vertex[] ToVertices(Vector3[] positions, Vector2[] uvs, Vector3[] normals)
        {
            if(positions.Length != normals.Length)
            {
                Console.WriteLine("position and normal lengths are not equal");
                return null;
            }

            Vertex[] vertices = ToVertices(positions, uvs);
            for (int i = 0; i < vertices.Length; i++)
            {
                vertices[i].normal = normals[i];
            }

            return vertices;
        }
    }
}