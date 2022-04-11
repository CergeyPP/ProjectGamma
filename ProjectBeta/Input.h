#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Event.h"

enum CallbackType
{
	MouseButtonCallback,
	KeyCallback,
	MouseCallback,

	CallbackTypeMax
};

struct CallbackInfo {
	CallbackInfo(CallbackType Type, int button, int action, int mode, float mousex, float mousey, float mDeltaX, float mDeltaY)
		: type(Type), button(button), action(action), mode(mode), mousex(mousex), mousey(mousey), mDeltaX(mDeltaX), mDeltaY(mDeltaY) { }

	CallbackType type;
	int button;
	int action;
	int mode;
	float mousex, mousey;
	float mDeltaX, mDeltaY;
};

class IInputable {
public:
	virtual void handleCallback(CallbackInfo&) = 0;
};

class Input
{
public:

	static void mouseButtonCallback(GLFWwindow* win, int button, int action, int mode);
	static void keyCallback(GLFWwindow* win, int button, int scancode, int action, int mode);
	static void mouseCursorCallback(GLFWwindow*, double x, double y);

	static Event<IInputable, CallbackInfo&> inputEvent;

private:

	static float mousePosX, mousePosY;
};

