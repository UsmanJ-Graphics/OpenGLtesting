#include "opengl.h"
#include"renderer.h"
#include"IndexBuffer.h"
#include"vertexbuffer.h"
#include"VertexArray.h"
#include"vertexBufferLayout.h"
#include"shader.h"
#include"Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"test/TestClearColor.h"
#include "test/Test.h"
#include "test/TestClearColor.h"
#include"test/TestTexture.h"



#define PI 3.14159265359f
struct ShapeData{
	std::vector<float>positions;
		std::vector<unsigned int>indices;
};

ShapeData CreateCircleData(float radius, int segments) {
 ShapeData data;
 //Center vertex
	data.positions.push_back(0.0f);//first vertex is the center of the circle
	data.positions.push_back(0.0f);
	//Texture coordinate for the center
	data.positions.push_back(0.5f);//texture coordinate for the center
	data.positions.push_back(0.5f);

	for (int i = 0; i < segments; i++) {
		float thetha = 2.0f * PI * float(i) / float(segments);
		data.positions.push_back(radius * cosf(thetha));
		data.positions.push_back(radius * sinf(thetha));
		//Texture coordinates for the circle vertices
		data.positions.push_back(0.5f + 0.5f * cosf(thetha));
		data.positions.push_back(0.5f + 0.5f * sinf(thetha));
	}
	for (int i = 0; i < segments; i++) {
		data.indices.push_back(0);//center vertex
		data.indices.push_back(i + 1);
		//current vertex on the circle
		if (i != segments - 1) data.indices.push_back(i + 2);
		else
			data.indices.push_back(1);
			}
	return data;
}

ShapeData CreateSqaureData(float size) {
	ShapeData data;
	float s = size / 2.0f;
	data.positions = {
	-s,-s, 0.0f,0.0f,//bottom left

	 s,-s, 1.0f,0.0f,//bottom right
	
	 s,s, 1.0f,1.0f,//top right
	
	 -s,s, 0.0f,1.0f//top left
	};
	data.indices = {
		0,1,2,
		2,3,0
	};
	return data;

}
void UpdateColors(float& r, float& g, float& b, float& Ri, float& Gi, float& bi) {
	auto bounce = [](float& val, float& inc) {
		val += inc;
		if (val > 1.0f || val < 0.0f) inc *= -1.0f;
		};
	bounce(r, Ri);
	bounce(g, Gi);
	bounce(b, bi);
}
int main() {

	Window window(1280, 720, "OpenGL Window");
	
	//Data Generation
	//ShapeData shape = CreateCircleData(0.5f,655);
	//ShapeData shape2 = CreateSqaureData(0.5f);

	//OpenGl Setup
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		// 
		//VertexArray va;
		//VertexBuffer vb(shape.positions.data(), shape.positions.size() * sizeof(float));
		////VertexBuffer vbs(shape2.positions.data(), shape.positions.size() * sizeof(float));

		//VertexBufferLayout layout;
		//layout.Push<float>(2);
		//layout.Push<float>(2);
		//va.AddBuffer(vb, layout);
		//VertexArray vaos;
		//VertexBuffer vbt(shape2.positions.data(), shape2.positions.size() * sizeof(float));

		//vaos.AddBuffer(vbt, layout);
		////va.AddBuffer(vbs, layout);
		//	 
		//IndexBuffer ib(shape.indices.data(), shape.indices.size());
		//IndexBuffer ib2(shape2.indices.data(), shape2.indices.size());
		//unsigned int indexcount = shape.indices.size();
		//glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f);
		//glm::mat4 view=glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		//
		//Shader shader("src/basic.shader");
		//shader.Bind();
	
		//shader.SetUniform4f("u_color", 0.0f,0.0f, 0.0f, 1.0f);
		//
	
		//Texture texture("res/textures/earth.png");
		//texture.Bind();
		//shader.SetUniform1i("u_texture", 0);
		//va.Unbind();
	 //   vb.Unbind();
	 //   ib.Unbind();
		//shader.Unbind();

		//
		//// Color animation variables
		//float r = 0.0f, g = 0.3f, b = 0.8f;
		//float Ri = 0.002f, Gi = 0.001f, bi = 0.0015f; // Slowed down for smoothness
		//glm::vec3 translationA(-3.5,-2.5f, 0.0f);
		//glm::vec3 translationB(-2.5, -1.5f, 0.0f);

		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		Renderer renderer;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window.GetNativeWindow(), true);
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui::StyleColorsDark();
		// --- NEW POLYMORPHIC TEST MANAGMENT SETUP ---
		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		// Register all available tests here
		testMenu->RegisterTest  <test::TestClearColor>("Clear Color Sandbox");
		testMenu->RegisterTest  <test::TestTexture>("2D Texture Mapping");
		//testMenu->RegisterTest < <test::TestCoordinate>("Coordinate System");





		


		while (!window.shouldClose()) {
			// --- UPDATE LOGIC ---
		// (Color oscillation logic here)

			//UpdateColors(r, g, b, Ri, Gi, bi);
			renderer.Clear();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			if (currentTest) {
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();


				ImGui::Begin("Test Executive Control");

				if (currentTest != testMenu && ImGui::Button("<-Return to Test Menu"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}


	//	shader.Bind();
		//	
		//	//glDrawArrays(GL_TRIANGLES, 0, 6);
		//		{
		//			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
		//			glm::mat4 mvp = proj * view * model;

		//			shader.SetUniformMat4f("u_MVP", mvp);
		//			renderer.Draw(va, ib, shader);

		//		}
		//		{
		//			shader.Bind();
		//			//shader.SetUniform4f("u_color", r, g, b, 1.0f);
		//			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
		//			glm::mat4 mvp = proj * view * model;


		//			shader.SetUniformMat4f("u_MVP", mvp);

		//			renderer.Draw(vaos, ib2, shader);
		//		}
		//	//glm::vec4 vp(0.0f, 0.0f, 0.0f, 1.0f);
		//	//glm::vec4 result = proj * vp;


		//	
		//	
		//	
		//	{
		//	  ImGui::Begin("Control Panel");
		//	  ImGui::SliderFloat3("Translation A", &translationA.x, -4.0f, 4.0f);
		//	  ImGui::SliderFloat3("Translation B", &translationB.x, -4.0f, 4.0f);
		//	 
		//	  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		//	ImGui::End();
		//}


			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


			window.swapBuffers();


			window.pollEvents();


		}
		if (currentTest != testMenu)
			delete currentTest;
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();


	return 0;

}
