#include <cassert>

#include "PhysicSystem.h"

bool PhysicSystem::instanced_ = false;
PhysicSystem* PhysicSystem::system_ = nullptr;

PhysicSystem* PhysicSystem::get() {
	if (!instanced_) {
		system_ = new PhysicSystem();

		instanced_ = true;
	}

	return system_;
}

PhysicSystem::PhysicSystem() {

	assert(!instanced_);

	foundation_ = PxCreateFoundation(PX_PHYSICS_VERSION, PhysxAllocator_, PhysxErrorCallback_);

	assert(foundation_ != nullptr);

	pvd_ = physx::PxCreatePvd(*foundation_);
	physics_ = PxCreateBasePhysics(PX_PHYSICS_VERSION, *foundation_, physx::PxTolerancesScale(), true, pvd_);
}

PhysicSystem::~PhysicSystem() {

	instanced_ = false;
	system_ = nullptr;

	physics_->release();
	pvd_->release();
	foundation_->release();
}