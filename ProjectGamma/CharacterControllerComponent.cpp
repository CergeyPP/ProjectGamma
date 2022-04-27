#include "CharacterControllerComponent.h"
#include "Converters.h"

void CharacterControllerComponent::prepareToSimulation()
{
    //controller_->setPosition(glmVec3ToPhysXExtendedVec3(getRoot()->getPos()));
    if (enableGravity) {
        move(glm::vec3(0, -9.81, 0), Scene::get().getDeltaTime());
    }
}

void CharacterControllerComponent::fetchResults()
{
    getRoot()->setPos(PhysXExtendedVec3ToglmVec3(controller_->getPosition()));
}

physx::PxController* CharacterControllerComponent::getController()
{
    return controller_;
}

void CharacterControllerComponent::move(glm::vec3 moveVector, float deltaTime)
{
    const physx::PxControllerFilters filter(filterData_, filterCallback_, CCTfilterCallback_);

    controller_->move(glmVec3ToPhysXVec3(moveVector * deltaTime /*+ glm::vec3(0, -9.81, 0) * (float)enableGravity*/), 0.0001, deltaTime, filter);
}

physx::PxController* CharacterControllerComponent::initController(float radius, float height, physx::PxMaterial* material)
{
    releaseController();
    physx::PxCapsuleControllerDesc desc;
    desc.setToDefault();
    desc.position = glmVec3ToPhysXExtendedVec3(getRoot()->getPos());
    desc.radius = radius;
    desc.height = height;
    desc.material = material;
    desc.slopeLimit = 0;
    desc.contactOffset = 0.1;
    desc.stepOffset = 0.1;
    desc.invisibleWallHeight = 0;
    desc.maxJumpHeight = 0;
    desc.reportCallback = nullptr;

    Scene& scene = Scene::get();
    auto controllerManager = scene.getPxControllerManager();
    
    controller_ = controllerManager->createController(desc);
    controller_->getActor()->wakeUp();
    //controller_->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
    return controller_;
}

void CharacterControllerComponent::releaseController()
{
    if (controller_ != nullptr) {
        controller_->release();
        controller_ = nullptr;
    }
}

CharacterControllerComponent::CharacterControllerComponent(GameObject* root)
    : Component(root)
{
    controller_ = nullptr;
    filterData_ = nullptr;
    filterCallback_ = nullptr;
    CCTfilterCallback_ = nullptr;

    Scene& scene = Scene::get();
    scene.addPhysicElement(this);
}

CharacterControllerComponent::~CharacterControllerComponent()
{
    if (filterData_ != nullptr) {
        delete filterData_;
    }

    releaseController();
}
