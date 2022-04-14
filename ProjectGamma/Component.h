#pragma once
#include "GameObject.h"

class Component {
public:

	GameObject* getRoot() const { return root_; }

	bool isActive() { return active_; }
	virtual void setActive(bool active);

protected:

	bool active_;

	Component(GameObject* root);
	virtual ~Component() {}

	GameObject* root_;

	friend GameObject;
};