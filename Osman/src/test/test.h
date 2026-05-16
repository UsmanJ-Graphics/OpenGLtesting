#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<functional>
#include "iamgui/imgui.h"
#include "iamgui/imgui_impl_glfw.h"
#include "iamgui/imgui_impl_opengl3.h"

namespace test
{
	class Test	
	{
	public:
		Test(){}
		virtual ~Test() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

};

	//Declaration of Meny System
class TestMenu : public Test
{
	Test*& m_CurrentTest;
	std::vector<std::pair<std::string, std::function<Test* ()>>> m_Test;

public:
	TestMenu(Test*& currentTestPointer):m_CurrentTest(currentTestPointer)
	{
	}
	~TestMenu() override {}
	void OnImGuiRender()override{
		ImGui::Text("---SELECT A TEST CASE---"); 
		ImGui::Separator();
		for (const auto& testPair : m_Test)
		{
			if (ImGui::Button(testPair.first.c_str(), ImVec2(200, 40)))
			{
				m_CurrentTest = testPair.second();
			}
		}
	}

	// method to register test classes cleanly
	template<typename T>
	void RegisterTest(const std::string& name) {
		std::cout << "Registering Test : " << name << std::endl;
		m_Test.push_back(std::make_pair(name, []() { return new T(); }));
	}

};
}