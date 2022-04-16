#include "InputComponent.h"
#include "CameraComponent.h"
#include <string>

void InputComponent::setActive(bool active)
{
	Input& input = Input::get();

	if (active_ == active) return;
	if (active) {
		hookTo(&input.dispatcherByName["Scroll"]);
		hookTo(&input.dispatcherByName["Horizontal"]);
		hookTo(&input.dispatcherByName["Vertical"]);
		hookTo(&input.dispatcherByName["Look"]);
		hookTo(&input.dispatcherByName["Click"]);
	}
	else {
		unhook(&input.dispatcherByName["Scroll"]);
		unhook(&input.dispatcherByName["Horizontal"]);
		unhook(&input.dispatcherByName["Vertical"]);
		unhook(&input.dispatcherByName["Look"]);
		unhook(&input.dispatcherByName["Click"]);
	}
	Component::setActive(active);
}

void InputComponent::onEvent(Event& event)
{
	switch (event.getType()) {
	case EventType::CLICK_EVENT:
	{
		ClickEvent& click = (ClickEvent&)event;
		std::cout << "Clicked " << click.button << " with mode" << click.mode << std::endl;
		break;
	}
	case EventType::SCROLLED_EVENT:
	{
		ScrollEvent& scrollEv = ((ScrollEvent&)event);
		std::cout << "Scrolled " << scrollEv.offset.y << std::endl;
		CameraComponent* camera = (CameraComponent*)getRoot()->getComponent<CameraComponent>()[0];
		camera->FOV -= scrollEv.offset.y/10;
		break;
	}
	case EventType::HORIZONTAL_EVENT:
	{
		HorizontalEvent& horizontalEv = (HorizontalEvent&)event;

		std::cout << "Move right " << horizontalEv.value << std::endl;

		__raise onHorizontal(horizontalEv.value);

		break;
	}
	case EventType::VERTICAL_EVENT:
	{
		VerticalEvent& verticalEv = (VerticalEvent&)event;

		

		std::cout << "Move up " << verticalEv.value << std::endl;

		__raise onVertical(verticalEv.value);

		break;
	}
	case EventType::LOOK_EVENT:
	{
		LookEvent& lookEv = (LookEvent&)event;
		std::cout << "Looked " << lookEv.offset.x << ":" << lookEv.offset.y << std::endl;

		__raise onLook(lookEv.offset);

		break;
	}
	default:
	{
		std::cout << "Unknown event" << std::endl;
		break;
	}
	}
}

InputComponent::InputComponent(GameObject* root) : Component(root), IEventable(nullptr)
{
}

InputComponent::~InputComponent()
{
}
