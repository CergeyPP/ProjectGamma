#include "Input.h"

void Input::mouseButtonCallback(GLFWwindow* win, int button, int action, int mode) {
	double mx, my;
	glfwGetCursorPos(win, &mx, &my);
	CallbackInfo info(MouseButtonCallback, button, action, mode, mx, my, 0,0);
	inputEvent(info);
}

void Input::keyCallback(GLFWwindow* win, int button, int scancode, int action, int mode) {
	double mx, my;
	glfwGetCursorPos(win, &mx, &my);
	CallbackInfo info(KeyCallback, button, action, mode, mx, my, 0, 0);
	inputEvent(info);
}

void Input::mouseCursorCallback(GLFWwindow*, double x, double y) {
	CallbackInfo info(MouseCallback, 8, GLFW_REPEAT, 0, x, y, mousePosX - x, mousePosY - y);
	inputEvent(info);

	mousePosX = x;
	mousePosY = y;
}

Event<IInputable, CallbackInfo&> Input::inputEvent;
float Input::mousePosX;
float Input::mousePosY;