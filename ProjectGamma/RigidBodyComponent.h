#pragma once
#include "PxPhysicsAPI.h"
#include "Component.h"
#include "PhysicElement.h"

class RigidBodyComponent :
    public Component, PhysicElement
{
public:

    void setShape(physx::PxShape* shape);
    physx::PxRigidDynamic* initializeDynamic();
    physx::PxRigidStatic* initializeStatic();

    void prepareToSimulation() override;
    void fetchResults() override;

    physx::PxRigidActor* getActor();

    bool isStatic() {
        return static_;
    }

private:

    bool static_;

    RigidBodyComponent(GameObject* root);
    ~RigidBodyComponent() override;
    
    physx::PxRigidActor* rigidActor_;

    friend GameObject;
};

