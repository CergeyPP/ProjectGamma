#include "GameObject.h"
#include "Converters.h"
#include <glm/gtx/matrix_decompose.hpp>

glm::mat4 GameObject::getTransformMatrix()
{
    glm::mat4 matrix = glm::scale(glm::mat4(1), scale_);
    matrix = glm::rotate(matrix, rotation_.w, glm::vec3(rotation_.x, rotation_.y, rotation_.z));
    matrix = glm::translate(matrix, position_);
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
    rotation_ = glm::quat(0, 0, 0, 1);
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
}

void GameObject::applyChanges()
{
}
