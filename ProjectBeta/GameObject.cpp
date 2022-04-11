#include "GameObject.h"

std::vector<ComponentManager*> GameObject::getComponents() {

	std::vector<ComponentManager*> components(components_.size());
	for (auto elem : components_) {
		components.push_back(elem);
	}

	return components;
}

void GameObject::addComponent(ComponentManager* compManager) {
	components_.push_back(compManager);
}
void GameObject::addComponent(Component* component) {
	components_.push_back(new ComponentManager(this, component));
}

bool GameObject::isEnabled() {
	return enabled_;
}

void GameObject::setEnabled(bool enabled) {
	enabled_ = enabled;
}

GameObject* GameObject::getParent() {
	return parent_;
}

std::vector<GameObject*>& GameObject::getChilren() {
	return children_;
}

void GameObject::addChild(GameObject* child) {

	if (this == child) return;

	auto iter = std::find(children_.begin(), children_.end(), child);
	if (iter < children_.end())
		return;

	if (child->getParent() != nullptr) {
		child->getParent()->removeChild(child);
	}

	children_.push_back(child);
	child->parent_ = this;
}

void GameObject::removeChild(GameObject* child) {

	if (this == child) return;

	auto iter = std::find(children_.begin(), children_.end(), child);
	if (iter == children_.end())
		return;

	children_.erase(iter);
	child->parent_ = nullptr;
}

GameObject::GameObject(physx::PxTransform trans) {
	transform = trans;
}

GameObject::~GameObject() {
	for (auto elem : this->components_) {
		delete elem;
	}
}