#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Event.h"
#include <iostream>
#include <cstdlib>

class Window
{
public:

	static Window& get() { static Window win(1280, 720, "ProjectGamma"); return win; }

	GLFWwindow* getGLFWwindow();

	glm::vec2 getSize();

	const char* getTitle();

	EventDispatcher dispatcher;

private:

	Window(int width, int height, const char* title);
	~Window();
	const char* title_;
	int width_; int height_;
	GLFWwindow* window_;

	static void MouseButtonCallback(GLFWwindow* win, int button, int action, int mods);
	static void KeyCallback(GLFWwindow* win, int button, int scancode, int action, int mods);
	static void MouseCursorCallback(GLFWwindow* win, double xpos, double ypos);
	static void ScrollCallback(GLFWwindow* win, double xoffset, double yoffset);
};

