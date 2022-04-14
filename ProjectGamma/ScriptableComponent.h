#pragma once
#include "Component.h"
#include "ComponentManager.h"
#include "ObjectPool.h"

class ScriptableComponent :
    protected Component
{
public:

    static ComponentManager* create(GameObject* root);


    void destroy() override;

protected:

    virtual void Start() {};
    virtual void Update(float deltaTime) {};
    virtual void OnDestroying() {};

private:

    void onSwap(int newIndex) override;
    void Activate() override;
    void Deactivate() override;

    friend class ObjectPool<ScriptableComponent>;

};

