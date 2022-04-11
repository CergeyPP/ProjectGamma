#pragma once
#include "Component.h"

class GameObject;

class ComponentManager
{
public:

	ComponentManager(GameObject* parent, Component* component);
	~ComponentManager();

	GameObject* parent();
	Component* get();

private:

	GameObject* parent_;
	Component* component_;

	friend class Component;
};

#include "GameObject.h"