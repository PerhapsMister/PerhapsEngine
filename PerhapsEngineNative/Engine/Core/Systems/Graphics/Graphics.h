#ifndef PERHAPS_GRAPHICS
#define PERHAPS_GRAPHICS
#include "../../PerhapsPch.h"
#include "VertexArray.h"
#include "Shader.h"

#include "../EventSystem/EngineEvents.h"

namespace Perhaps
{
	class Graphics
	{
	public:

		enum class ClearMask
		{
			COLOR = 0x00004000, DEPTH = 0x00000100, STENCIL = 0x00000400,
			COLOR_DEPTH = (int)COLOR | (int)DEPTH, COLOR_STENCIL = (int)COLOR | (int)STENCIL,
			COLOR_DEPTH_STENCIL = (int)COLOR | (int)DEPTH | (int)STENCIL
		};

		static void Clear(ClearMask mask)
		{
			glClear((int)mask);
		}

		static void SetClearColor(Color clearColor)
		{
			glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		}

		static void Draw(VertexArray* va)
		{
			if (va->Bind())
			{
				glDrawElements(GL_TRIANGLES, va->indices.size(), GL_UNSIGNED_INT, 0);
			}
			else
			{
				conlog("Failed to bind vertex array");
			}
		}

		void OnResize(const Event& event)
		{
			ResizeEvent& e = (ResizeEvent&)event;
			glViewport(0, 0, e.newSize.x, e.newSize.y);
		}

	private:
		static Graphics initializer;

		int mId0;
		Graphics()
		{
			mId0 = EventDispatcher::Subscribe(ResizeEvent::descriptor, std::bind(&Graphics::OnResize, this, std::placeholders::_1));
		}

		~Graphics()
		{
			EventDispatcher::UnSubscribe(mId0);
		}

	};
	Graphics Graphics::initializer;


	PAPI void Graphics_Clear(Graphics::ClearMask mask)
	{
		Graphics::Clear(mask);
	}

	PAPI void Graphics_SetClearColor(Color color)
	{
		Graphics::SetClearColor(color);
	}

	PAPI void Graphics_Draw(VertexArray* va)
	{
		Graphics::Draw(va);
	}
}

#endif