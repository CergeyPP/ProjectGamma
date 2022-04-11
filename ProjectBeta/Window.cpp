#include "Window.h"
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

	glfwSetWindowUserPointer(window_, this);

	glfwMakeContextCurrent(window_);
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

	std::cout << "Key Pressed " << button << std::endl;
}

void Window::MouseCursorCallback(GLFWwindow* w, double xpos, double ypos)
{
	Window& window = *(Window*)glfwGetWindowUserPointer(w);

	std::cout << "Mouse Moved " << xpos << ":" << ypos << std::endl;
}

void Window::ScrollCallback(GLFWwindow* w, double xoffset, double yoffset)
{
	Window& window = *(Window*)glfwGetWindowUserPointer(w);

	std::cout << "Scrolled with offset " << yoffset << std::endl;
}

void Window::MouseButtonCallback(GLFWwindow* w, int button, int action, int mods)
{
	Window& window = *(Window*)glfwGetWindowUserPointer(w);

	std::cout << "Mouse Button Pressed " << button << std::endl;
}
