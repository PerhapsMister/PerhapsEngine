#include "VertexArray.h"

namespace Perhaps
{
	VertexArray* VertexArray::bound;

	void VertexArray::BindCheck()
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