#include "Component.h"

Component::Component() {
	rootManager_ = nullptr;
	enabled_ = false;
}

Component::~Component() {
	if (rootManager_ != nullptr) {
		destroy();
	}
}

void Component::destroy() {
	rootManager_ = nullptr;
}

ComponentManager* Component::createManager(GameObject* root) {
	ComponentManager* manager = new ComponentManager(root, this);
	rootManager_ = manager;
	setEnabled(true);

	return manager;
}

void Component::setEnabled(bool enable) {
	if (enable == enabled_) return;

	enabled_ = enable;
	if (enabled_) 
		Activate();
	else 
		Deactivate();


}

void Component::setManagerPointer(Component* pointer) {
	rootManager_->component_ = pointer;
}

bool Component::isEnabled() {
	return enabled_;
}

GameObject* Component::getObject() {
	return rootManager_->parent_;
}

