#pragma once
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "PxPhysicsAPI.h"

class GameObject;

class Scene
{
public:

	static Scene& get() { static Scene scene; return scene; }

	void load(std::string filePath = "DebugScene");

	GameObject* instantiate(GameObject* root, glm::vec3 pos = glm::vec3(0));
	void destroy(GameObject* object);

	std::vector<GameObject*> getObjects() { return gameObjects_; }

	void update(float deltaTime);

private:

	Scene();
	~Scene();
	
	void afterUpdate();

	std::vector<GameObject*> gameObjects_;

	std::vector<GameObject*> objectsToDestroy_;
	std::vector<GameObject*> objectsToInstantiate_;

	physx::PxDefaultAllocator pxAllocator_;
	physx::PxDefaultErrorCallback pxErrorCallback_;
	physx::PxFoundation* foundation_;
	physx::PxPvd* pvd_;
	physx::PxPhysics* physics_;
	physx::PxScene* scene_;

};

#include "GameObject.h"

