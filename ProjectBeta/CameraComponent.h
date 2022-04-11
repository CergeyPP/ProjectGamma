#pragma once
#include "Component.h"

template<class T>
class ObjectPool;

class CameraComponent :
    public Component
{
public:

    static ComponentManager* create(GameObject* root, float fov);

    void destroy() override;

    void onSwap(int newIndex) override;

    glm::mat4 getProjection();
    glm::mat4 getView();

    float getFOV() { return fov_; }

    CameraComponent();
    ~CameraComponent() override;

private:

    float fov_;
    float resolRatio_;

    void Activate() override;
    void Deactivate() override;

    friend ObjectPool<CameraComponent>;
};

#include "ObjectPool.h"