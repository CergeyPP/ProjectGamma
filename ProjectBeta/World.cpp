#include "World.h"
#include "PhysicSystem.h"
#include <cassert>
#include "CameraComponent.h"
#include "StaticMeshComponent.h"
#include "InputComponent.h"
#include "DrawSystem.h"

bool World::instanced_ = 0;
World* World::world_ = nullptr;

World* World::get() {
	if (!instanced_) {
		world_ = new World();
		instanced_ = true;
	}

	return world_;
}

World::World() {
	assert(!instanced_);

	//scene_ = PhysicSystem::get();
	
}

World::~World() {
	instanced_ = false;

	for (auto& elem : objects) {
		delete elem;
	}
}

void World::load(const char* filename) {
	if (filename != "Debug world") {
		// do some fucking loading after all
	}
	else {

		GameObject* object = new GameObject(physx::PxTransform(physx::PxVec3(2, 3, 4)));
		object->addComponent(CameraComponent::create(object, 90));
		object->addComponent(InputComponent::create(object));

		//DrawSystem::get()->cameraPool.swap(0, 1);

		objects.push_back(object);

		object = new GameObject(physx::PxTransform(physx::PxVec3(0, 0, 0)));

		object->addComponent(StaticMeshComponent::create(object, createBoxMesh(glm::vec3(1)), Material(Simplest_Shader)));

		objects.push_back(object);

	}
}

void World::update(float deltaTime) {
		
}

std::vector<GameObject*>& World::getObjects() {
	return objects;
}