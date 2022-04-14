#pragma once
#include "Component.h"
#include "Event.h"
#include "Input.h"

class InputComponent :
    public Component, IEventable
{
public:

    void setActive(bool active) override;

    void onEvent(Event& event) override;

protected:
    InputComponent(GameObject* root);
    ~InputComponent() override;

    friend GameObject;
};

