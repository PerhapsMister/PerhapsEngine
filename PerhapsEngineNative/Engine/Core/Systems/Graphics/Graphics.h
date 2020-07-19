#ifndef PERHAPS_GRAPHICS
#define PERHAPS_GRAPHICS
#include "../../PerhapsPch.h"
#include "VertexArray.h"
#include "Shader.h"

namespace Perhaps
{

	class Graphics
	{
	public:

		enum class ColorMask
		{
			COLOR = 0x00004000, DEPTH = 0x00000100, STENCIL = 0x00000400,
			COLOR_DEPTH = (int)COLOR | (int)DEPTH, COLOR_STENCIL = (int)COLOR | (int)STENCIL,
			COLOR_DEPTH_STENCIL = (int)COLOR | (int)DEPTH | (int)STENCIL
		};

		enum class EnableParam
		{
			DEPTH_TEST = GL_DEPTH_TEST,
			BLEND = GL_BLEND,
			STENCIL = GL_STENCIL
		};

		enum class BlendFunc
		{
			ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
		};

		static void Clear(ColorMask mask)
		{
			glClear((int)mask);
		}

		static void SetClearColor(Color clearColor)
		{
			glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		}

		static void Draw(VertexArray& va)
		{
			if (va.Bind())
			{
				glDrawElements(GL_TRIANGLES, va.indices.size(), GL_UNSIGNED_INT, 0);
			}
			else
			{
				conlog("Failed to bind vertex array");
			}
		}

		static void DrawLine()
		{
			
		}

		static void SetDrawDimensions(int x, int y, int width, int height)
		{
			glViewport(x, y, width, height);
		}

		static void Enable(EnableParam param, bool value)
		{
			GLenum p = (GLenum)param;

			if (value)
			{
				glEnable(p);
			}
			else
			{
				glDisable(p);
			}
		}

		static void SetBlendFunc(BlendFunc func)
		{
			GLenum f = (GLenum)func;
			glBlendFunc(GL_SRC_ALPHA, f);
		}

	private:

	};

	PAPI void Graphics_Clear(Graphics::ColorMask mask);

	PAPI void Graphics_SetClearColor(Color color);

	PAPI void Graphics_Draw(VertexArray* va);

	PAPI void Graphics_Enable(Graphics::EnableParam param, bool value);
}


#endif