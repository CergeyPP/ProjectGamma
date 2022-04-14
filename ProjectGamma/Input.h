#pragma once
#include <map>
#include "Event.h"
#include "Window.h"
#include "IEventable.h"

class Input : public IEventable
{
public:
	static Input& get() { static Input input; return input; }

	void onEvent(Event& event) override;

	std::map<std::string, EventDispatcher> dispatcherByName;

private:

	glm::vec2 mousePos;

	Input();
	~Input() override;
};

