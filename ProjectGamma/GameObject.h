#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include "PxPhysicsAPI.h"
#include "Scene.h"

class Component;

class GameObject
{
public:

	glm::mat4 getTransformMatrix();
	physx::PxTransform getPxTransform();

	void setTransformMatrix(glm::mat4 matrix);
	void setPxTransform(physx::PxTransform transform);

	glm::vec3 getPos();
	glm::quat getRot();
	glm::vec3 getScale();

	void setScale(glm::vec3 scale);

	void setRot(glm::quat rot);

	void getPos(glm::vec3 pos);

	void translate(glm::vec3 translateVec);
	void rotate(glm::quat newRotate);
	void toScale(glm::vec3 newScale);

	GameObject* getRoot() const { return root_; }
	std::vector<GameObject*>& getChildren() { return children_; }

	bool isActive();
	void setActive(bool active);

	template<typename T = Component>
	std::vector<Component*> getComponent() {
		std::vector<Component*> comp;
		for (auto& elem : components_) {
			if (T* component = dynamic_cast<T*>(elem)) {
				comp.push_back(component);
			}
		}

		return comp;
	}

	template<typename T = Component>
	std::vector<Component*> getComponentInRoot() {
		std::vector<Component*> comp;
		if (root_ == nullptr) return comp;
		for (auto& elem : root_->components_) {
			if (T* component = dynamic_cast<T*>(elem)) {
				comp.push_back(component);
			}
		}

		return comp;
	}

	template<typename T = Component>
	std::vector<Component*> getComponentInChild() {
		std::vector<Component*> comp;
		for (auto& child : children_)
			for (auto& elem : components_) {
				if (T* component = dynamic_cast<T*>(elem)) {
					comp.push_back(component);
				}
			}

		return comp;
	}

	template<typename T>
	Component* instantiateComponent() {
		Component* comp = new T(this);
		components_.push_back(comp);
		return comp;
	}

	Scene* getScene() { return scene_; }

private:

	bool active_;

	GameObject* root_;
	std::vector<GameObject*> children_;
	
	glm::vec3 position_;
	glm::quat rotation_;
	glm::vec3 scale_;

	std::vector<Component*> components_;

	GameObject(Scene* scene_, GameObject* root = nullptr);
	~GameObject();

	void init();
	void update(float deltaTime);
	void applyChanges();

	Scene* scene_;

	friend Scene;
};

#include "Component.h"