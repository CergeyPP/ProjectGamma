#include "Event.h"

EventType Event::getType()
{
	return type_;
}

Event::~Event()
{
}

Event::Event(EventType type)
{
	type_ = type;
}

ScrollEvent::ScrollEvent(glm::vec2 offs) : Event(EventType::SCROLLED_EVENT)
{
	offset = offs;

}

ScrollEvent::~ScrollEvent()
{
}

KeyEvent::KeyEvent(int action, int but, int m) : Event(EventType((int)EventType::KEY_RELEASED_EVENT + action))
{
	
	button = but;
	mode = m;
}

KeyEvent::~KeyEvent()
{
}

MouseMovedEvent::MouseMovedEvent(glm::vec2 pos) : Event(EventType::MOUSE_MOVED_EVENT)
{
	position = pos;
}

MouseMovedEvent::~MouseMovedEvent()
{
}

MouseButtonEvent::MouseButtonEvent(int action, int but, int m) : Event(EventType((int)EventType::MOUSEBUTTON_RELEASED_EVENT + action))
{
	button = but;
	mode = m;
}

MouseButtonEvent::~MouseButtonEvent()
{
}
