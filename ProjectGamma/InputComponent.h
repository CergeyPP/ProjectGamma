#pragma once
#include "Component.h"
#include "Event.h"
#include "Input.h"

[event_source(native)]
class InputComponent :
    public Component, IEventable
{
public:

    void setActive(bool active) override;

    void onEvent(Event& event) override;

public:

    __event void onVertical(float&);
    __event void onHorizontal(float&);
    __event void onLook(glm::vec2&);

protected:
    InputComponent(GameObject* root);
    ~InputComponent() override;

    friend GameObject;
};

