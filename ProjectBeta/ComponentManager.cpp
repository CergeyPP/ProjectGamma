#include "ComponentManager.h"

ComponentManager::ComponentManager(GameObject* parent, Component* component) {
	parent_ = parent;
	component_ = component;
}

ComponentManager::~ComponentManager() {
	component_->destroy();
}

GameObject* ComponentManager::parent() {
	return parent_;
}

Component* ComponentManager::get() {
	return component_;
}