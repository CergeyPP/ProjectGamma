#include "DrawableComponent.h"
#include "DrawSystem.h"

DrawableComponent::DrawableComponent(GameObject* root) : Component(root) {

    DrawSystem::get().addDrawable(this);
}

DrawableComponent::~DrawableComponent() {

    DrawSystem::get().removeDrawable(this);
}
