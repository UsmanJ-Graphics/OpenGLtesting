#pragma once
#include"test.h"
#include"Texture.h"
#include"Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "vertexBufferLayout.h"
#include <memory>

namespace test
{
	class TestTexture : public Test
	{
	public:
		TestTexture();
		~TestTexture() override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender()override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		float m_MixValue;
	};
}