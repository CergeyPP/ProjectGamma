#pragma once
#include "GameObject.h"

class ComponentManager;

class Component
{
public:

	GameObject* getObject();

	bool isEnabled();
	virtual void setEnabled(bool enable);

	virtual void onSwap(int newIndex) = 0;

	Component();
	virtual ~Component();

protected:

	virtual void destroy();

	ComponentManager* createManager(GameObject* root);

	virtual void Activate() = 0;
	virtual void Deactivate() = 0;

	void setManagerPointer(Component* pointer);

	ComponentManager* rootManager_;
	bool enabled_;

	friend ComponentManager;
};

#include "ComponentManager.h"