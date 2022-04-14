#include "Window.h"
#include "Input.h"
#include <iostream>

GLFWwindow* Window::getGLFWwindow()
{
	return window_;
}

glm::vec2 Window::getSize()
{
	return glm::vec2(width_, height_);
}

const char* Window::getTitle()
{
	return title_;
}

Window::Window(int width, int height, const char* title)
{
	width_ = width;
	height_ = height;
	title_ = title;

	window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);

	if (!window_)
		exit(-1);

	glfwMakeContextCurrent(window_);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << glewGetErrorString(GLEW_VERSION) << std::endl;
	}
	glViewport(0, 0, width_, height_);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);*/

	glClearColor(0.3, 0.3, 0.3, 1.f);

	glfwSetWindowUserPointer(window_, this);
	glfwSetMouseButtonCallback(window_, MouseButtonCallback);
	glfwSetCursorPosCallback(window_, MouseCursorCallback);
	glfwSetKeyCallback(window_, KeyCallback);
	glfwSetScrollCallback(window_, ScrollCallback);

}

Window::~Window() {
	glfwSetWindowShouldClose(window_, true);
}

void Window::KeyCallback(GLFWwindow* w, int button, int scancode, int action, int mods)
{
	Window& window = *(Window*)glfwGetWindowUserPointer(w);

	//std::cout << "Key Pressed " << button << std::endl;

	KeyEvent event(action, button, mods);

	Input::get().onEvent(event);
	//window.dispatcher(event);
}

void Window::MouseCursorCallback(GLFWwindow* w, double xpos, double ypos)
{
	Window& window = *(Window*)glfwGetWindowUserPointer(w);

	//std::cout << "Mouse Moved " << xpos << ":" << ypos << std::endl;

	MouseMovedEvent event(glm::vec2(xpos, ypos));

	Input::get().onEvent(event);
	//window.dispatcher(event);
}

void Window::ScrollCallback(GLFWwindow* w, double xoffset, double yoffset)
{
	Window& window = *(Window*)glfwGetWindowUserPointer(w);

	//std::cout << "Scrolled with offset " << yoffset << std::endl;

	ScrollEvent event(glm::vec2(xoffset, yoffset));

	Input::get().onEvent(event);
	//window.dispatcher(event);
}

void Window::MouseButtonCallback(GLFWwindow* w, int button, int action, int mods)
{
	Window& window = *(Window*)glfwGetWindowUserPointer(w);

	MouseButtonEvent event(action, button, mods);

	Input::get().onEvent(event);
	//window.dispatcher(event);
}
