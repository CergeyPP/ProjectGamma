#pragma once
#include "ScriptableComponent.h"

#include "CharacterControllerComponent.h"

[event_receiver(native)]
class MoveScript :
    public ScriptableComponent
{
public:

    void Update(float deltaTime) override;

private:

    CharacterControllerComponent* controller_;

    MoveScript(GameObject* root);
    ~MoveScript();

    void onLook(glm::vec2& value);
    void onVertical(float& value);
    void onHorizontal(float& value);

    glm::vec2 moveVector;

    friend GameObject;
};

