#include "InputComponent.h"
#include <iostream>

InputComponent::InputComponent()
{
}

ComponentManager* InputComponent::create(GameObject* root)
{
	InputSystem* system = InputSystem::get();

	InputComponent* comp = system->inputComponentPool.instansiate();

	return comp->createManager(root);
}

InputComponent::~InputComponent()
{
}

void InputComponent::onSwap(int newIndex)
{
	InputSystem* system = InputSystem::get();
	if (rootManager_ != nullptr)
		setManagerPointer(&system->inputComponentPool.objects[newIndex]);
}

void InputComponent::Activate()
{
	InputSystem::get()->inputComponentPool.activate(this);
}

void InputComponent::mouseReceiver(CallbackInfo& info)
{
	

}

void InputComponent::keyReceiver(CallbackInfo& info)
{
	
}

void InputComponent::destroy() {
	if (isEnabled())
		setEnabled(false);
	InputSystem::get()->inputComponentPool.destroy(this);

	Component::destroy();
}

void InputComponent::Deactivate()
{
	InputSystem::get()->inputComponentPool.deactivate(this);
}
