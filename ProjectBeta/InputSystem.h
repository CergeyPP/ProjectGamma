#pragma once
#include "Input.h"
#include "Defines.h"
#include "ObjectPool.h"

class InputComponent;

class InputSystem : public IInputable
{
public:

	static InputSystem* get();
	~InputSystem();

	void handleCallback(CallbackInfo& info) override;

	ObjectPool<InputComponent> inputComponentPool;

private:

	InputSystem();

	static bool instanced_;
	static InputSystem* system_;

};

#include "InputComponent.h"

