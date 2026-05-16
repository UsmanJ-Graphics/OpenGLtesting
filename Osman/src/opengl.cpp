#include"opengl.h"


Window::Window(int width, int height, const std::string& title) :
	m_width(width), m_height(height), m_title(title) {
	if (!init()) {
		glfwTerminate();
	}

}
Window::~Window() {
	glfwTerminate();
}
bool Window::init() {
	if (!glfwInit()) {
		std::cout << "Failed to Initialize GLFW" << std::endl;
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_Window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	if (!m_Window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);
	GLenum err = glewInit();
	if (err != GLEW_OK) {

		std::cout << "Failed to initialize GLEW" << glewGetErrorString(err) << std::endl;
		return false;
	}
	std::cout << "Open GL VERSION :" << glGetString(GL_VERSION) << std::endl;
	return true;
}
bool Window::shouldClose() const {
	return glfwWindowShouldClose(m_Window);
}
void Window::swapBuffers() const {
	glfwSwapBuffers(m_Window);
}
void Window::pollEvents() const {
	glfwPollEvents();
}
