#include "Component.h"

void Component::setActive(bool active)
{
	active_ = active;
}

Component::Component(GameObject* root)
{
	root_ = root;
	active_ = false;
}
