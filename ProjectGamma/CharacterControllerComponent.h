#pragma once
#include "Component.h"
#include "PhysicElement.h"
#include "PxPhysicsAPI.h"

class CharacterControllerComponent :
    public Component, PhysicElement
{
public:

    void prepareToSimulation() override;
    void fetchResults() override;

    physx::PxController* getController();

    bool enableGravity = 1;

    void move(glm::vec3 moveVector, float deltaTime);

    physx::PxController* initController(float radius, float height, physx::PxMaterial* material);

private:

    void releaseController();

    CharacterControllerComponent(GameObject* root);
    ~CharacterControllerComponent() override;

    physx::PxController* controller_;
    physx::PxFilterData* filterData_;
    physx::PxQueryFilterCallback* filterCallback_;
    physx::PxControllerFilterCallback* CCTfilterCallback_;

    friend GameObject;

};

