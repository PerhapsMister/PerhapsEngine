#ifndef PERHAPS_VERTEX_ARRAY
#define PERHAPS_VERTEX_ARRAY
#include "../../PerhapsPch.h"

class VertexArray
{
public:
	VertexArray()
	{

	}

	~VertexArray()
	{
		if(bound == this)
			Unbind();
	}

	void UploadData()
	{
		if (vao == -1)
		{
			glGenVertexArrays(1, &vao);
		}

		if (vbo == -1)
		{
			glGenBuffers(1, &vbo);
		}

		if (ebo == -1)
		{
			glGenBuffers(1, &ebo);
		}

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), &positions[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), &indices[0], GL_STATIC_DRAW);

		if (bound != this && bound != nullptr)
		{
			bound->Bind();
		}
		else if (bound == nullptr)
		{
			Unbind();
		}
	}

	bool Bind()
	{
		if (vao != -1)
		{
			glBindVertexArray(vao);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			bound = this;
			return true;
		}

		return false;
	}

	static void Unbind()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		bound = nullptr;
	}

	std::vector<float> positions;
	std::vector<unsigned int> indices;
private:
	static VertexArray* bound;

	unsigned int vao = -1, vbo = -1, ebo = -1;
	
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

PAPI void VA_SetPositions(VertexArray* va, float* positions, int count)
{
	va->positions = std::vector<float>(positions, positions + count);
}

PAPI void VA_GetPositions(VertexArray* va, float** positions, int* count)
{
	*positions = &va->positions[0];
	*count = va->positions.size();
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

PAPI void VA_GetIndices(VertexArray* va, unsigned int** indices, int* count)
{
	*indices = &va->indices[0];
	*count = va->indices.size();
}

PAPI void VA_SetIndices(VertexArray* va, unsigned int* indices, int count)
{
	va->indices = std::vector<unsigned int>(indices, indices + count);
}

#endif 