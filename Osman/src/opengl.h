#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
class Window {
public:
	Window(int width, int height, const std::string& title);
	~Window();
	GLFWwindow* GetNativeWindow() const
	{
		return m_Window;
	}
	bool shouldClose()const;
	void swapBuffers()const;
	void pollEvents()const;
private:
	GLFWwindow* m_Window;
	int m_width, m_height;
	std::string m_title;
	bool init();

};
