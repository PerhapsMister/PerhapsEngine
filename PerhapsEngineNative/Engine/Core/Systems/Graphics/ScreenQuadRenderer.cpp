#include "ScreenQuadRenderer.h"
#include "../../Application.h"

namespace Perhaps
{
	class Application;
	
	void ScreenQuadRenderer::Initialize()
	{
		quadVa = new VertexArray();

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
		screenQuadShader = Shader::CompileShader(screenQuadVs, screenQuadFs);

		const std::vector<Vertex> vertices =
		{
			Vertex(-1, -1, 0, 0),//bottom left
			Vertex(1, -1, 1, 0),//bottom right
			Vertex(-1, 1, 0, 1),//top left
			Vertex(1, 1, 1,1),//top right
		};
		quadVa->vertices = vertices;
		

		const std::vector<int> indices =
		{
			0,1,2,
			1,3,2
		};
		quadVa->indices = indices;
		quadVa->UploadData();
	}

	void ScreenQuadRenderer::Render(RenderTexture& rt)
	{
		Window* window = Application::GetInstance()->GetWindow();

		glm::vec2 dimensions = window->GetDimensions();
		Graphics::SetDrawDimensions(0, 0, dimensions.x, dimensions.y);

		Texture2D::UnbindAll();
		rt.GetColorAttachment()->Bind(0);
		screenQuadShader->Bind();
		screenQuadShader->SetInt("tex", 0);
		Graphics::Draw(*quadVa);

		Graphics::SetDrawDimensions(0, 0, 1280, 720);
	}

	void ScreenQuadRenderer::Cleanup()
	{
		delete(screenQuadShader);
		delete(quadVa);
	}
}