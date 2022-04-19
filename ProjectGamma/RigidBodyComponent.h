#pragma once
#include "PxPhysicsAPI.h"
#include "Component.h"

class RigidBodyComponent :
    public Component
{
public:

    void setShape(physx::PxShape* shape);
    physx::PxRigidDynamic* initializeDynamic();
    physx::PxRigidStatic* initializeStatic();

    void prepareToSimulation();
    void fetchResults();

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

