#pragma once
#include "ScriptableComponent.h"
#include "CharacterControllerComponent.h"

[event_receiver(native)]
class CharMoveScript :
    public ScriptableComponent
{
public:

    void Update(float deltaTime) override;

private:

    CharacterControllerComponent* controller_;

    CharMoveScript(GameObject* root);
    ~CharMoveScript();

    void onLook(glm::vec2& value);
    void onVertical(float& value);
    void onHorizontal(float& value);

    glm::vec2 moveVector;

    friend GameObject;
};