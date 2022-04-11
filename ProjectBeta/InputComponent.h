#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Component.h"
#include "ComponentManager.h"
#include "Input.h"
#include "InputSystem.h"
#include <string>
#include "ObjectPool.h"

class InputComponent :
    public Component 
{
public:

    static ComponentManager* create(GameObject*);

    ~InputComponent() override;

    void onSwap(int newIndex) override;

    //boost::signals2::signal<void(CallbackInfo&)> mouseReceiver;
    //boost::signals2::signal<void(CallbackInfo&)> keyReceiver;

    void mouseReceiver(CallbackInfo& info);
    void keyReceiver(CallbackInfo& info);

    void destroy() override;

private:

    InputComponent();

    void Activate() override;
    void Deactivate() override;

    friend ObjectPool<InputComponent>;
};

