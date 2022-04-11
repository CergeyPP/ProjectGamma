#pragma once
#include "PxPhysicsAPI.h"

class PhysicSystem
{
public:

	static PhysicSystem* get();
	~PhysicSystem();

private:

	PhysicSystem();

	physx::PxDefaultAllocator PhysxAllocator_;
	physx::PxDefaultErrorCallback PhysxErrorCallback_;
	physx::PxFoundation* foundation_;

	physx::PxPvd* pvd_;
	physx::PxPhysics* physics_;

	static bool instanced_;
	static PhysicSystem* system_;
};

