#ifndef PERHAPS_VERTEX_ARRAY
#define PERHAPS_VERTEX_ARRAY
#include "../../PerhapsPch.h"
namespace Perhaps
{
	struct Vertex
	{
	public:
		Vertex() : position(0,0,0), uv(0,0), normal(0,0,0)
		{
		}

		Vertex(float x, float y) :position(x,y,0), uv(0,0), normal(0,0,0)
		{

		}
		Vertex(float x, float y, float z) : position(x,y,z), uv(0,0), normal(0,0,0)
		{
			
		}

		Vertex(float x, float y, float u, float v) :position(x, y, 0), uv(u, v), normal(0, 0, 0)
		{

		}

		Vertex(float x, float y, float z, float u, float v) : position(x, y, z), uv(u,v), normal(0,0,0)
		{

		}
		

		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
	};

	class VertexArray
	{
	public:

		VertexArray()
		{

		}

		~VertexArray()
		{
			if (bound == this)
			{
				Unbind();
			}

			if (vao != 0)
			{
				glDeleteVertexArrays(1, &vao);
			}

			if (vbo != 0)
			{
				glDeleteBuffers(1, &vbo);
			}

			if (ebo != 0)
			{
				glDeleteBuffers(1, &ebo);
			}
		}

		void UploadData()
		{
			if (vao == 0)
			{
				glGenVertexArrays(1, &vao);
			}
			if (vbo == 0)
			{
				glGenBuffers(1, &vbo);
			}
			if (ebo == 0)
			{
				glGenBuffers(1, &ebo);
			}

			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

			const int stride = sizeof(Vertex);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
			glEnableVertexAttribArray(0);//position

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 3));
			glEnableVertexAttribArray(1);//uv

			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 5));
			glEnableVertexAttribArray(2);//normal

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

			BindCheck();
		}

		bool Bind()
		{
			if (vao == 0)
			{
				return false;
			}

			glBindVertexArray(vao);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			bound = this;
			return true;
		}

		static void Unbind()
		{
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			bound = nullptr;
		}

		std::vector<Vertex> vertices;
		std::vector<int> indices;

	private:
		static VertexArray* bound;
		unsigned int vao = 0, vbo = 0, ebo = 0;

		void BindCheck();

	};

	PAPI VertexArray* VA_Create();
	PAPI void VA_Delete(VertexArray* va);
	PAPI void VA_SetVertices(VertexArray* va, Vertex* vertices, int count);
	PAPI void VA_GetVertices(VertexArray* va, Vertex** vertices, int* count);
	PAPI void VA_GetIndices(VertexArray* va, int** indices, int* count);
	PAPI void VA_SetIndices(VertexArray* va, int* indices, int count);
	PAPI void VA_Upload(VertexArray* va);
	PAPI bool VA_Bind(VertexArray* va);
	PAPI void VA_Unbind();
}
#endif 