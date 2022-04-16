#include "LightComponent.h"
#include "DrawSystem.h"

void LightComponent::setDistance(float distance)
{
	linear = 4.5 / distance;
	quadratic = 75 / distance / distance;
}

float LightComponent::getDistance(float distance)
{
	return 4.5 / linear;
}

LightComponent::LightComponent(GameObject* root) : Component(root) {
	DrawSystem::get().addLight(this);

	cutoff = 0;
	linear = 1;
	quadratic = 1;
	type = LightType::LIGHTTYPE_COUNT;
	diffuse = glm::vec3(0);
	specular = glm::vec3(0);

}

LightComponent::~LightComponent() {
	DrawSystem::get().removeLight(this);
}