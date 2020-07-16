#ifndef PERHAPS_VERTEX_ARRAY
#define PERHAPS_VERTEX_ARRAY
#include "../../PerhapsPch.h"
namespace Perhaps
{
	struct Vertex
	{
	public:
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
				Unbind();
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

		void BindCheck()
		{
			if (bound != nullptr)
			{
				bound->Bind();
			}
			else
			{
				Unbind();
			}
		}

	};
	VertexArray* VertexArray::bound = nullptr;

	PAPI VertexArray* VA_Create()
	{
		VertexArray* va = new VertexArray();
		return va;
	}

	PAPI void VA_Delete(VertexArray* va)
	{
		delete(va);
	}

	PAPI void VA_SetVertices(VertexArray* va, Vertex* vertices, int count)
	{
		va->vertices = std::vector<Vertex>(vertices, vertices + count);
	}

	PAPI void VA_GetVertices(VertexArray* va, Vertex** vertices, int* count)
	{
		*vertices = &va->vertices[0];
		*count = va->vertices.size();
	}

	PAPI void VA_GetIndices(VertexArray* va, int** indices, int* count)
	{
		*indices = &va->indices[0];
		*count = va->indices.size();
	}

	PAPI void VA_SetIndices(VertexArray* va, int* indices, int count)
	{
		va->indices = std::vector<int>(indices, indices + count);
	}

	PAPI void VA_Upload(VertexArray* va)
	{
		va->UploadData();
	}

	PAPI bool VA_Bind(VertexArray* va)
	{
		return va->Bind();
	}

	PAPI void VA_Unbind()
	{
		VertexArray::Unbind();
	}
}
#endif 