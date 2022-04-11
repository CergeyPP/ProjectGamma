#include <cassert>

#include "InputSystem.h"
#include "DrawSystem.h"

bool InputSystem::instanced_ = false;
InputSystem* InputSystem::system_ = nullptr;

InputSystem* InputSystem::get() {
	if (!instanced_){
		system_ = new InputSystem();
		instanced_ = true;
	}
	return system_;
}

InputSystem::InputSystem() : inputComponentPool(MAX_INPUTS) {
	assert(!instanced_);
	
	Input::inputEvent.addListener(this, &IInputable::handleCallback);
}

InputSystem::~InputSystem() {
	instanced_ = false;
	system_ = nullptr;

	Input::inputEvent.deleteListener(this, &IInputable::handleCallback);
}

void InputSystem::handleCallback(CallbackInfo& info) {
	/*if (info.type == KeyCallback && info.button == GLFW_KEY_SPACE && info.action == GLFW_PRESS) {
		std::cout << "Received Space\n";
		if (DrawSystem::get()->cameraPool.getActiveCount() > 0)
			DrawSystem::get()->cameraPool.getAll()[DrawSystem::get()->cameraPool.getActiveCount() - 1].setEnabled(1 - DrawSystem::get()->cameraPool.getAll()[DrawSystem::get()->cameraPool.getActiveCount() - 1].isEnabled());
	}*/

	auto pool = inputComponentPool.getAll();

	if (info.action == MouseCallback)
		for (int i = 0; i < inputComponentPool.getActiveCount(); i++) {
			pool[i].mouseReceiver(info);
		}
	else
		for (int i = 0; i < inputComponentPool.getActiveCount(); i++) {
			pool[i].keyReceiver(info);
		}
}