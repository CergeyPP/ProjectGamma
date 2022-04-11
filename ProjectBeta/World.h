#pragma once
#ifndef CORE_H
#define CORE_H

#include <vector>
#include "PxPhysicsAPI.h"

class GameObject;

class World {
public:

	static World* get();

	void load(const char* filename = "Debug world");

	~World();

	void update(float deltaTime);
	//void physxUpdate(float deltaTime);
	std::vector<GameObject*>& getObjects();

private:

	World();

	std::vector<GameObject*> objects;

	physx::PxScene* scene_;

	static bool instanced_;
	static World* world_;
};

#include "GameObject.h"

#endif