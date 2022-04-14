#pragma once
#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "IEventable.h"

enum class EventType : int {
	KEY_RELEASED_EVENT = 1,
	KEY_PRESSED_EVENT,
	KEY_REPEATED_EVENT,
	MOUSE_MOVED_EVENT,
	MOUSEBUTTON_RELEASED_EVENT,
	MOUSEBUTTON_PRESSED_EVENT,
	SCROLLED_EVENT,

	HORIZONTAL_EVENT,
	VERTICAL_EVENT,
	LOOK_EVENT,
	CLICK_EVENT,

	EVENT_COUNT,
};

class Event {
public:

	EventType getType();
	virtual ~Event();

protected:
	Event(EventType type);

	EventType type_;
};

class EventDispatcher {
public:

	void operator()(Event& ev) {
		__raise dispatch(ev);
	}
	void add(IEventable* listener) {
		__hook(&EventDispatcher::dispatch, this, &IEventable::onEvent, listener);
	}
	void remove(IEventable* listener) {
		__unhook(&EventDispatcher::dispatch, this, &IEventable::onEvent, listener);
	}

private:
	__event void dispatch(Event&);
};

class ScrollEvent : public Event {
public:

	glm::vec2 offset;
	ScrollEvent(glm::vec2 offs);
	~ScrollEvent() override;
};

class KeyEvent : public Event {
public:

	int button;
	int mode;
	KeyEvent(int action, int but, int m);
	~KeyEvent() override;
};

class MouseMovedEvent : public Event {
public:

	glm::vec2 position;

	MouseMovedEvent(glm::vec2 pos);
	~MouseMovedEvent() override;
};

class MouseButtonEvent : public Event {
public:

	int button;
	int mode;
	MouseButtonEvent(int action, int but, int m);
	~MouseButtonEvent() override;
};

class ClickEvent : public MouseButtonEvent{
public:
	ClickEvent(int but, int mode) : MouseButtonEvent(GLFW_PRESS, but, mode) {
		type_ = EventType::CLICK_EVENT;
	}
};
class LookEvent : public MouseMovedEvent {
public:
	glm::vec2 offset;
	LookEvent(glm::vec2 pos) : MouseMovedEvent(pos) {
		type_ = EventType::LOOK_EVENT;
	}
};

class HorizontalEvent : public Event {
public:
	float value;
	HorizontalEvent(float v) : Event(EventType::HORIZONTAL_EVENT), value(v) {};
};

class VerticalEvent : public Event {
public:
	float value;
	VerticalEvent(float v) : Event(EventType::VERTICAL_EVENT), value(v) {}
};

#include "IEventable.h"