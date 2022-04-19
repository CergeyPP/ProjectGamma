#include "RigidBodyComponent.h"
#include "Scene.h"

void RigidBodyComponent::setShape(physx::PxShape* shape)
{
    rigidActor_->attachShape(*shape);
}

physx::PxRigidDynamic* RigidBodyComponent::initializeDynamic()
{
    physx::PxPhysics* physics = Scene::get().getPxPhysics();
    physx::PxScene* pxscene = Scene::get().getPxScene();

    if (rigidActor_ != nullptr) {
        pxscene = Scene::get().getPxScene();
        pxscene->removeActor(*rigidActor_);
        rigidActor_->release();
        rigidActor_ = nullptr;
    }

    physx::PxRigidDynamic* dynamic = physics->createRigidDynamic(root_->getPxTransform());
    pxscene->addActor(*dynamic);
    rigidActor_ = dynamic;

    return dynamic;
}

physx::PxRigidStatic* RigidBodyComponent::initializeStatic()
{
    physx::PxPhysics* physics = Scene::get().getPxPhysics();
    physx::PxScene* pxscene = Scene::get().getPxScene();

    if (rigidActor_ != nullptr) {
        pxscene = Scene::get().getPxScene();
        pxscene->removeActor(*rigidActor_);
        rigidActor_->release();
        rigidActor_ = nullptr;
    }

    physx::PxRigidStatic* rstatic = physics->createRigidStatic(root_->getPxTransform());
    pxscene->addActor(*rstatic);
    rigidActor_ = rstatic;

    return rstatic;

}

void RigidBodyComponent::prepareToSimulation()
{
    if (rigidActor_ != nullptr) {
        rigidActor_->setGlobalPose(root_->getPxTransform());
    }
}

void RigidBodyComponent::fetchResults()
{
    if (rigidActor_ != nullptr) {
        root_->setPxTransform(rigidActor_->getGlobalPose());
    }
}

physx::PxRigidActor* RigidBodyComponent::getActor()
{
    return rigidActor_;
}

RigidBodyComponent::RigidBodyComponent(GameObject* root)
    : Component(root)
{
    rigidActor_ = nullptr;
    static_ = 0;

    Scene& scene = Scene::get();
    scene.addRigidComponent(this);
}

RigidBodyComponent::~RigidBodyComponent()
{
    if (rigidActor_ != nullptr) {
        physx::PxScene* pxscene = Scene::get().getPxScene();
        pxscene->removeActor(*rigidActor_);
        rigidActor_->release();
        rigidActor_ = nullptr;
    }
}
