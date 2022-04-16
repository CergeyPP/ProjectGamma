#include "Input.h"

void Input::onEvent(Event& event)
{
	switch (event.getType()) {
	case EventType::KEY_PRESSED_EVENT:
	{
		KeyEvent& keyEvent = (KeyEvent&)event;
		switch (keyEvent.button) {
		case GLFW_KEY_D: {
			HorizontalEvent pushEvent(1);
			dispatcherByName["Horizontal"](pushEvent);
			break;
		}
		case GLFW_KEY_A: {
			HorizontalEvent pushEvent(-1);
			dispatcherByName["Horizontal"](pushEvent);
			break;
		}
		case  GLFW_KEY_W: {
			VerticalEvent pushEvent(1);
			dispatcherByName["Vertical"](pushEvent);
			break;
		}
		case GLFW_KEY_S: {
			VerticalEvent pushEvent(-1);
			dispatcherByName["Vertical"](pushEvent);
			break;
		}
		case GLFW_KEY_ENTER: {
			Window& window = Window::get();
			bool cursorFlag = glfwGetInputMode(window.getGLFWwindow(), GLFW_CURSOR) - GLFW_CURSOR_NORMAL;
			std::cout << "Cursor flag: " << cursorFlag << std::endl;
			glfwSetInputMode(window.getGLFWwindow(), GLFW_CURSOR, (!cursorFlag) ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
			break;
		}
		}
		break;
	}
	case EventType::KEY_RELEASED_EVENT:
	{
		KeyEvent& keyEvent = (KeyEvent&)event;
		if (keyEvent.button == GLFW_KEY_D) {
			HorizontalEvent pushEvent(-1);
			dispatcherByName["Horizontal"](pushEvent);
			break;
		}
		if (keyEvent.button == GLFW_KEY_A) {
			HorizontalEvent pushEvent(1);
			dispatcherByName["Horizontal"](pushEvent);
			break;
		}
		if (keyEvent.button == GLFW_KEY_W) {
			VerticalEvent pushEvent(-1);
			dispatcherByName["Vertical"](pushEvent);
			break;
		}
		if (keyEvent.button == GLFW_KEY_S) {
			VerticalEvent pushEvent(1);
			dispatcherByName["Vertical"](pushEvent);
			break;
		}

		break; 
	}
	case EventType::MOUSEBUTTON_PRESSED_EVENT:
	{
		MouseButtonEvent& button = (MouseButtonEvent&)event;
		ClickEvent click = ClickEvent(button.button, button.mode);
		dispatcherByName["Click"](click);

		break;
	}
	/*
	case EventType::MOUSEBUTTON_RELEASED_EVENT:

		break;*/
	case EventType::MOUSE_MOVED_EVENT:
	{ 
		MouseMovedEvent& mouseEvent = (MouseMovedEvent&)event;
		if ((glfwGetInputMode(Window::get().getGLFWwindow(), GLFW_CURSOR) - GLFW_CURSOR_NORMAL)) {
			LookEvent look = LookEvent(mouseEvent.position);
			look.offset = mouseEvent.position - mousePos;
			dispatcherByName["Look"](look);
		}

		mousePos = mouseEvent.position;
		break;
	}
	case EventType::SCROLLED_EVENT:
		dispatcherByName["Scroll"](event);
		break;
	}
}

Input::Input() : IEventable(&Window::get().dispatcher)
{
	dispatcherByName["Horizontal"] = EventDispatcher();
	dispatcherByName["Vertical"] = EventDispatcher();
	dispatcherByName["Look"] = EventDispatcher();
	dispatcherByName["Scroll"] = EventDispatcher();
	dispatcherByName["Click"] = EventDispatcher();
}

Input::~Input()
{
}
