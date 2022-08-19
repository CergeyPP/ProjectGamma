#include "Scene.h"
#include "InputComponent.h"
#include "Input.h"
#include "CameraComponent.h"
#include "StaticMeshComponent.h"
#include "RigidBodyComponent.h"
#include "LightComponent.h"
#include "MoveScript.h"
#include "CharacterControllerComponent.h"
#include "DrawSystem.h"
#include "CharMoveScript.h"

void Scene::load(std::string filePath)
{
    for (auto& elem : objectsToInstantiate_) {
        delete elem;
    }
    for (auto& elem : gameObjects_) {
        delete elem;
    }
    for (auto& elem : objectsToDestroy_) {
        delete elem;
    }

    objectsToDestroy_.clear();
    objectsToInstantiate_.clear();
    gameObjects_.clear();

    scene_->release();
    physx::PxSceneDesc desc(physics_->getTolerancesScale());
    desc.gravity = physx::PxVec3(0, -9.81, 0);
    if (!desc.cpuDispatcher) {
        auto mCpuDispatcher = physx::PxDefaultCpuDispatcherCreate(4);
        if (!mCpuDispatcher)
            std::cout << "FATAL DISPATCHER!" << std::endl;
        desc.cpuDispatcher = mCpuDispatcher;
    }
    desc.filterShader = physx::PxDefaultSimulationFilterShader;
    scene_ = physics_->createScene(desc);

    controllerManager_ = PxCreateControllerManager(*scene_);

    if (filePath != "DebugScene") {
        //load scene from file
    }
    else {

        ambientColor = glm::vec4(0.2);
        DrawSystem& drawSystem = DrawSystem::get();

        {
            auto obj = instantiate(nullptr);
            obj->translate(glm::vec3(0, 20, 0));
            obj->instantiateComponent<InputComponent>();
            CameraComponent* camera = (CameraComponent*)obj->instantiateComponent<CameraComponent>();
            camera->FOV = 90.f;
            CharacterControllerComponent* character = (CharacterControllerComponent*)obj->instantiateComponent<CharacterControllerComponent>();
            auto material = physics_->createMaterial(0.5, 0.5, 1);
            character->initController(1, 0.1, material);
            character->enableGravity = 1;
            obj->instantiateComponent<CharMoveScript>();
        }

        {
            auto floor = instantiate(nullptr, glm::vec3(0, -5, 0));
            RigidBodyComponent* rBody = (RigidBodyComponent*)floor->instantiateComponent<RigidBodyComponent>();
            auto bodyStatic = rBody->initializeStatic();
            auto material = physics_->createMaterial(0.5, 0.5, 0);
            auto shape = physics_->createShape(physx::PxBoxGeometry(10, 0.05, 10), *material, true);
            rBody->setShape(shape);
            shape->release();
            bodyStatic->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);

            StaticMeshComponent* mesh = (StaticMeshComponent*)floor->instantiateComponent<StaticMeshComponent>();
            mesh->setMesh(&createBoxMesh(glm::vec3(20, 0.1, 20)));
            mesh->mesh->material = new Material(Light_Shader);
            mesh->mesh->material->tex2DParam["material.Albedo"] = drawSystem.getTexture(glm::vec4(0.7, 0.7, 0.7, 1));
            mesh->mesh->material->tex2DParam["material.Specular"] = drawSystem.getTexture(glm::vec4(0.3));
            mesh->mesh->material->floatParam["material.shininess"] = 8;
        }

        for (int i = 20; i <= 2; i++)
            for (int j = 20; j <= 2; j++)
            {
                auto cube = instantiate(nullptr, glm::vec3(j * 2, 5, i * 2));
                StaticMeshComponent* mesh = (StaticMeshComponent*)cube->instantiateComponent<StaticMeshComponent>();
                mesh->setMesh(&createBoxMesh(glm::vec3(2)));
                mesh->mesh->material = new Material(Light_Shader);
                mesh->mesh->material->tex2DParam["material.Albedo"] = drawSystem.getTexture("container.png");
                mesh->mesh->material->tex2DParam["material.Specular"] = drawSystem.getTexture("containerSpecular.png");
                mesh->mesh->material->floatParam["material.shininess"] = 1024;

                RigidBodyComponent* rBody = (RigidBodyComponent*)cube->instantiateComponent<RigidBodyComponent>();
                auto bodyDynamic = rBody->initializeDynamic();
                auto material = physics_->createMaterial(0.5, 0.5, 1);
                auto shape = physics_->createShape(physx::PxBoxGeometry(1, 1, 1), *material, true);
                rBody->setShape(shape);
                shape->release();
                bodyDynamic->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, false);
                bodyDynamic->setMass(4);
                bodyDynamic->setMassSpaceInertiaTensor(physx::PxVec3(1, 1, 1));
            }

        {
            auto sun = instantiate(nullptr);
            sun->position_ = glm::vec3(1, 3, 0);
            sun->rotation_ = glm::quat(glm::vec3(0, 0, -glm::pi<float>() / 4));
            LightComponent* light = (LightComponent*)sun->instantiateComponent<LightComponent>();
            light->light.diffuse = glm::vec4(1);
            light->light.specular = glm::vec4(1);
            light->light.type = LightType::DIRECTIONAL_LIGHT;
            StaticMeshComponent* mesh = (StaticMeshComponent*)sun->instantiateComponent<StaticMeshComponent>();
            mesh->setMesh(&createBoxMesh(glm::vec3(0.1, 0.05, 0.05)));
            mesh->mesh->material = new Material(Simplest_Shader);
            mesh->mesh->material->tex2DParam["Albedo"] = drawSystem.getTexture(glm::vec4(light->light.diffuse + light->light.specular) / 2.f);
        }

        {
            auto lamp = instantiate(nullptr);
            lamp->position_ = glm::vec3(1, 0, 2);
            LightComponent* light = (LightComponent*)lamp->instantiateComponent<LightComponent>();
            light->light.diffuse = glm::vec4(1);
            light->light.specular = glm::vec4(1, 0, 1, 1);
            light->light.type = LightType::POINT_LIGHT;
            light->setDistance(25);
            StaticMeshComponent* mesh = (StaticMeshComponent*)lamp->instantiateComponent<StaticMeshComponent>();
            mesh->setMesh(&createBoxMesh(glm::vec3(0.05, 0.05, 0.05)));
            mesh->mesh->material = new Material(Simplest_Shader);
            mesh->mesh->material->tex2DParam["Albedo"] = drawSystem.getTexture(glm::vec4(light->light.diffuse + light->light.specular) / 2.f);
        }

        {
            auto lamp = instantiate(nullptr);
            lamp->position_ = glm::vec3(-3, -2, -1);
            LightComponent* light = (LightComponent*)lamp->instantiateComponent<LightComponent>();
            light->light.diffuse = glm::vec4(1, 0, 0, 1);
            light->light.specular = glm::vec4(0, 1, 0, 1);
            light->light.type = LightType::POINT_LIGHT;
            light->setDistance(50);
            StaticMeshComponent* mesh = (StaticMeshComponent*)lamp->instantiateComponent<StaticMeshComponent>();
            mesh->setMesh(&createBoxMesh(glm::vec3(0.05, 0.05, 0.05)));
            mesh->mesh->material = new Material(Simplest_Shader);
            mesh->mesh->material->tex2DParam["Albedo"] = drawSystem.getTexture(glm::vec4(light->light.diffuse + light->light.specular) / 2.f);
        }

        {
            auto blaster = instantiate(nullptr);
            blaster->position_ = glm::vec3(0, 10, 0);
            auto meshRoot = instantiate(blaster);
            meshRoot->position_ = glm::vec3(0, -1, 0);
            meshRoot->rotation_ = glm::quat(glm::vec3(0, -3.14/2, 0));
            StaticMeshComponent* mesh = (StaticMeshComponent*)meshRoot->instantiateComponent<StaticMeshComponent>();
            Mesh* modelmesh = drawSystem.getMesh("egirl/egirl.obj");
            mesh->setMesh(modelmesh);
            meshRoot->setScale(glm::vec3(0.01));
            RigidBodyComponent* rBody = (RigidBodyComponent*)blaster->instantiateComponent<RigidBodyComponent>();
            auto bodyDynamic = rBody->initializeDynamic();
            auto material = physics_->createMaterial(0, 0, 0);
            auto shape = physics_->createShape(physx::PxCapsuleGeometry(1, 0.1), *material, true);

            rBody->setShape(shape);
            shape->release();
            bodyDynamic->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, false);
            bodyDynamic->setMass(4);
            bodyDynamic->setMassSpaceInertiaTensor(physx::PxVec3(1, 1, 1));

        }
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
    deltaTime_ = deltaTime;

    for (auto elem : gameObjects_) {
        elem->update(deltaTime);
    }

    for (auto elem : physicElements_) {
        elem->prepareToSimulation();
    }

    scene_->simulate(deltaTime);
    scene_->fetchResults(true);

    for (auto elem : physicElements_) {
        elem->fetchResults();
    }

    afterUpdate();
}

physx::PxScene* Scene::getPxScene()
{
    return scene_;
}

physx::PxPhysics* Scene::getPxPhysics()
{
    return physics_;
}

physx::PxControllerManager* Scene::getPxControllerManager()
{
    return controllerManager_;
}

void Scene::addPhysicElement(PhysicElement* comp)
{
    physicElements_.push_back(comp);
}

Scene::Scene()
{
    ambientColor = glm::vec4(0);

    foundation_ = PxCreateFoundation(PX_PHYSICS_VERSION, pxAllocator_, pxErrorCallback_);

    pvd_ = physx::PxCreatePvd(*foundation_);
    physics_ = PxCreateBasePhysics(PX_PHYSICS_VERSION, *foundation_, physx::PxTolerancesScale(), true, pvd_);

    physx::PxSceneDesc desc(physics_->getTolerancesScale());
    desc.gravity = physx::PxVec3(0, -9.81, 0);
    scene_ = physics_->createScene(desc);
    controllerManager_ = nullptr;
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
