#include "GameObject.h"
#include "Converters.h"
#include "ScriptableComponent.h"
#include <glm/gtx/matrix_decompose.hpp>

glm::mat4 GameObject::getTransformMatrix()
{
    glm::mat4 scale = glm::scale(glm::mat4(1), scale_);
    glm::mat4 rotate = glm::mat4_cast(rotation_);
    glm::mat4 translate = glm::translate(glm::mat4(1), position_);
    glm::mat4 matrix = translate * rotate * scale;
    return (root_ != nullptr) ? root_->getTransformMatrix() * matrix : matrix;
    //return glm::mat4(1);
}

physx::PxTransform GameObject::getPxTransform()
{
    physx::PxTransform transform = physx::PxTransform(glmVec3ToPhysXVec3(position_));
    transform.q = glmQuatToPhysXQuat(rotation_);
    return transform;
}

void GameObject::setTransformMatrix(glm::mat4 matrix)
{
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(matrix, scale_, rotation_, position_, skew, perspective);
    rotation_ = glm::conjugate(rotation_);
}

void GameObject::setPxTransform(physx::PxTransform transform)
{
    position_ = PhysXVec3ToglmVec3(transform.p);
    rotation_ = PhysXQuatToglmQuat(transform.q);
}

glm::vec3 GameObject::getPos()
{
    return position_;
}

glm::quat GameObject::getRot()
{
    return rotation_;
}

glm::vec3 GameObject::getScale()
{
    return scale_;
}

void GameObject::setScale(glm::vec3 scale) {
    scale_ = scale;
}

void GameObject::setRot(glm::quat rot) {
    rotation_ = rot;
}

void GameObject::getPos(glm::vec3 pos) {
    position_ = pos;
}

void GameObject::translate(glm::vec3 translateVec)
{
    position_ += translateVec;
}

void GameObject::rotate(glm::quat newRotate)
{
    rotation_ = newRotate * rotation_;
}

void GameObject::toScale(glm::vec3 newScale)
{
    scale_ = newScale;
}

bool GameObject::isActive()
{
    return active_;
}

void GameObject::setActive(bool active)
{
    active_ = active;
}

GameObject::GameObject(Scene* scene, GameObject* root)
{
    root_ = root;
    scene_ = scene;
    active_ = false;
    position_ = glm::vec3(0);
    rotation_ = glm::quat(1,0,0,0);
    scale_ = glm::vec3(1);
}

GameObject::~GameObject()
{
    for (auto& elem : children_) {
        scene_->destroy(elem);
    }
    for (auto& elem : components_) {
        delete elem;
    }
}

void GameObject::init()
{
    setActive(true);
    for (auto& elem : components_) {
        elem->setActive(true);
    }
}

void GameObject::update(float deltaTime)
{
    auto scripts = getComponent<ScriptableComponent>();
    for (auto& elem : scripts) {
        ScriptableComponent* script = (ScriptableComponent*)elem;
        script->Update(deltaTime);
    }
}

void GameObject::applyChanges()
{
}
