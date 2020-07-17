#include "Renderer2D.h"

namespace Perhaps
{

	void Renderer2D::Initialize()
	{
		const std::vector<Vertex> vertices =
		{
			Vertex(-1, -1, 0, 0),//bottom left
			Vertex(1, -1, 1, 0),//bottom right
			Vertex(-1, 1, 0, 1),//top left
			Vertex(1, 1, 1,1),//top right
		};
		va.vertices = vertices;

		const std::vector<int> indices =
		{
			0,1,2,
			1,3,2
		};

		va.indices = indices;
		va.UploadData();
		shrek = Importer::ImportTexture("D:\\Dev\\Dev\\PerhapsEngine\\PerhapsEngineEditor\\Images\\shrek.jpg", true);

		const std::string screenQuadVs =
			"#version 430 core\n"
			"layout(location = 0) in vec3 aPos;\n"
			"layout(location = 1) in vec2 aUv;\n"

			"out vec2 uv;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(aPos, 1.0);\n"
			"uv = aUv;\n"
			"}\n";

		const std::string screenQuadFs =
			"#version 430 core\n"
			"out vec4 FragColor;\n"
			"in vec2 uv;\n"
			"uniform sampler2D tex;\n"

			"void main()\n"
			"{\n"
			"vec4 color = texture(tex, uv);\n"
			"FragColor = color;\n"
			"}\n";
		shader = Shader::CompileShader(screenQuadVs, screenQuadFs);
	}

	void Renderer2D::Render(RenderTexture& rt)
	{
		Graphics::SetClearColor(Color(1, 0, 0, 1));
		rt.Bind();
		Graphics::Clear(Graphics::ColorMask::COLOR_DEPTH_STENCIL);

		shader->Bind();
		shader->SetInt("tex", 0);
		shrek->Bind(0);
		Graphics::Draw(va);
		rt.Unbind();
	}

	void Renderer2D::OnCleanup()
	{

	}
}