#pragma once
#include <vector>

class Event;
class EventDispatcher;

class IEventable {
public:

	virtual void onEvent(Event& ev) = 0;
	IEventable(EventDispatcher* dispatcher);
	virtual ~IEventable();

	void hookTo(EventDispatcher* dispatcher);
	void unhook(EventDispatcher* dispatcher);

protected:

	std::vector<EventDispatcher*> dispatcher_;
};

#include "Event.h"