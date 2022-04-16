#include "Scene.h"
#include "InputComponent.h"
#include "Input.h"
#include "CameraComponent.h"
#include "StaticMeshComponent.h"
#include "LightComponent.h"
#include "MoveScript.h"

void Scene::load(std::string filePath)
{
    objectsToDestroy_.clear();
    objectsToInstantiate_.clear();
    gameObjects_.clear();

    scene_->release();
    scene_ = physics_->createScene(physx::PxSceneDesc(physics_->getTolerancesScale()));

    if (filePath != "DebugScene") {
        //load scene from file
    }
    else {

        ambientColor = glm::vec4(0.7);

        auto obj = instantiate(nullptr);
        obj->translate(glm::vec3(0, 0, 0));
        obj->instantiateComponent<InputComponent>();
        CameraComponent* camera = (CameraComponent*)obj->instantiateComponent<CameraComponent>();
        camera->FOV = 90.f;
        obj->instantiateComponent<MoveScript>();

        auto cube = instantiate(nullptr);
        StaticMeshComponent* mesh = (StaticMeshComponent*)cube->instantiateComponent<StaticMeshComponent>();
        mesh->setMesh(createBoxMesh(glm::vec3(2)));
        mesh->material = Material(Light_Shader);
        mesh->material.tex2DParam["material.Albedo"] = Texture("container.png");
        mesh->material.tex2DParam["material.Specular"] = Texture("containerSpecular.png");
        mesh->material.floatParam["material.shininess"] = 8;

        auto sun = instantiate(nullptr);
        sun->position_ = glm::vec3(1, 3, 0);
        //sun->rotation_ = glm::quat(glm::vec3(0, 0, -glm::pi<float>()/4));
        LightComponent* light = (LightComponent*)sun->instantiateComponent<LightComponent>();
        light->diffuse = glm::vec3(1);
        light->specular = glm::vec3(1);
        light->type = LightType::DIRECTIONAL_LIGHT;
        //light->setDistance(40);
        mesh = (StaticMeshComponent*)sun->instantiateComponent<StaticMeshComponent>();
        mesh->setMesh(createBoxMesh(glm::vec3(0.1,0.05, 0.05)));
        mesh->material = Material(Simplest_Shader);
        mesh->material.tex2DParam["Albedo"] = Texture(glm::vec4(1));
    }
}

GameObject* Scene::instantiate(GameObject* root, glm::vec3 pos)
{
    GameObject* object = new GameObject(this, root);
    object->position_ = pos;

    objectsToInstantiate_.push_back(object);
    return object;
}

void Scene::destroy(GameObject* object)
{
    object->setActive(false);
    objectsToDestroy_.push_back(object);
}

void Scene::update(float deltaTime)
{
    for (auto elem : gameObjects_) {
        elem->update(deltaTime);
    }

    afterUpdate();
}

Scene::Scene()
{
    ambientColor = glm::vec4(0);

    foundation_ = PxCreateFoundation(PX_PHYSICS_VERSION, pxAllocator_, pxErrorCallback_);

    pvd_ = physx::PxCreatePvd(*foundation_);
    physics_ = PxCreateBasePhysics(PX_PHYSICS_VERSION, *foundation_, physx::PxTolerancesScale(), true, pvd_);

    physx::PxSceneDesc desc(physics_->getTolerancesScale());
    scene_ = physics_->createScene(physx::PxSceneDesc(physics_->getTolerancesScale()));

    load();
}

Scene::~Scene()
{
    scene_->release();
    physics_->release();
    pvd_->release();
    foundation_->release();
}

void Scene::afterUpdate()
{
    for (auto& elem : gameObjects_) {
        elem->applyChanges();
    }

    for (auto& elem : objectsToDestroy_) {
        auto iter = std::find(gameObjects_.begin(), gameObjects_.end(), elem);
        if (iter < gameObjects_.end()) {
            gameObjects_.erase(iter);
        }

        delete elem;
    }

    objectsToDestroy_.clear();


    for (auto& elem : objectsToInstantiate_) {
        gameObjects_.push_back(elem);
        elem->init();
    }

    objectsToInstantiate_.clear();
}
