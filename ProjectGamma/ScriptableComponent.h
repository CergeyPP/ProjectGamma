#pragma once
#include "Component.h"
#include "ObjectPool.h"

class ScriptableComponent :
    public Component
{
protected:

    virtual void Start() {};
    virtual void Update(float deltaTime) {};
    virtual void OnDestroying() {};

    ~ScriptableComponent();
    ScriptableComponent(GameObject* root);

private:

    friend GameObject;

};
