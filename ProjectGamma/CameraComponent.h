#pragma once
#include "Component.h"

class CameraComponent :
    public Component
{
public:

    float FOV;

private:

    CameraComponent(GameObject* root);
    ~CameraComponent() override;


    friend GameObject;
};