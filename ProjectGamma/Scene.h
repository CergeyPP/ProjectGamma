#pragma once
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "PxPhysicsAPI.h"

class GameObject;

class RigidBodyComponent;

class Scene
{
public:

	static Scene& get() { static Scene scene; return scene; }

	void load(std::string filePath = "DebugScene");

	GameObject* instantiate(GameObject* root, glm::vec3 pos = glm::vec3(0));
	void destroy(GameObject* object);

	std::vector<GameObject*> getObjects() { return gameObjects_; }

	void update(float deltaTime);

	glm::vec4 ambientColor;

	template<typename T>
	std::vector<GameObject*> findObjectsWith() {
		std::vector<GameObject*> objectList;
		for (auto elem : gameObjects_) {
			if (elem->getComponent<T>().size() > 0) {
				objectList.push_back(elem);
			}
		}

		return objectList;
	}

	physx::PxScene* getPxScene();
	physx::PxPhysics* getPxPhysics();

	void addRigidComponent(RigidBodyComponent* comp);

private:

	Scene();
	~Scene();
	
	void afterUpdate();

	std::vector<GameObject*> gameObjects_;

	std::vector<GameObject*> objectsToDestroy_;
	std::vector<GameObject*> objectsToInstantiate_;

	std::vector<RigidBodyComponent*> rigidBodies_;

	physx::PxDefaultAllocator pxAllocator_;
	physx::PxDefaultErrorCallback pxErrorCallback_;
	physx::PxFoundation* foundation_;
	physx::PxPvd* pvd_;
	physx::PxPhysics* physics_;
	physx::PxScene* scene_;

};

#include "GameObject.h"
//#include "RigidBodyComponent.h"

