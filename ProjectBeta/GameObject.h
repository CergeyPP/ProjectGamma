#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "PxPhysicsAPI.h"

class ComponentManager;
class Component;

class GameObject
{
public:

	physx::PxTransform transform;

	std::vector<ComponentManager*> getComponents();
	bool isEnabled();
	void setEnabled(bool enable);

	void addComponent(ComponentManager* compManager);
	void addComponent(Component* component);

	GameObject* getParent();
	std::vector<GameObject*>& getChilren();
	void addChild(GameObject* child);
	void removeChild(GameObject* child);

	template<typename T>
	ComponentManager* getComponent() {
		for (auto elem : components_) {
			if (T* comp = dynamic_cast<T*>(elem->getComponent())) {
				return elem;
			}
		}

		return nullptr;
	}

	GameObject(physx::PxTransform transf = physx::PxTransform(physx::PxIDENTITY()));
	~GameObject();

private:



	bool enabled_;
	std::vector<ComponentManager*> components_;
	std::vector<GameObject*> children_;
	GameObject* parent_;

};

#include "ComponentManager.h"
#include "Component.h"
