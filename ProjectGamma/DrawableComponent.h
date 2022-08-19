#pragma once
#include "Component.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Mesh.h"

class DrawableComponent :
    public Component
{
public:

    virtual void draw() = 0;

    Mesh* mesh;

protected:

    DrawableComponent(GameObject* root);
    ~DrawableComponent() override;

    friend GameObject;
};

