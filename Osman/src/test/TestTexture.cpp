#include"TestTexture.h"
#include"renderer.h"
#include "iamgui/imgui.h"

namespace test
{
	TestTexture::TestTexture() :m_MixValue(1.0f)
	{
		float Vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
		};
		unsigned int Indices[] = {
			0,1,2,
			2,3,0
		};
		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(Vertices, sizeof(Vertices));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_IBO = std::make_unique<IndexBuffer>(Indices, sizeof(Indices) / sizeof(unsigned int));
		m_Shader = std::make_unique<Shader>("src/basic.shader");
		m_Shader->Bind();
		m_Texture = std::make_unique<Texture>("res/textures/earth.png");
	}
	TestTexture::~TestTexture()
	{
	}
	void TestTexture::OnUpdate(float deltaTime)
	{
	}
	void TestTexture::OnRender()
	{
		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		m_Texture->Bind(0);
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_MixValue", m_MixValue);
		Renderer renderer;
		renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
	}
	void TestTexture::OnImGuiRender()
	{
		ImGui::SliderFloat("Texture Mix Alpha", &m_MixValue, 0.0f, 1.0f);
	}
}