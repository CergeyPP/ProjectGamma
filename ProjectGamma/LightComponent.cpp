#include "LightComponent.h"
#include "DrawSystem.h"

void LightComponent::setDistance(float distance)
{
	light.linear = 4.5 / distance;
	light.quadratic = 75 / distance / distance;
}

float LightComponent::getDistance(float distance)
{
	return 4.5 / light.linear;
}

LightComponent::LightComponent(GameObject* root) : Component(root) {
	DrawSystem::get().addLight(this);

	light.cutoff = 0;
	light.linear = 1;
	light.quadratic = 1;
	light.type = LightType::LIGHTTYPE_COUNT;
	light.diffuse = glm::vec4(0);
	light.specular = glm::vec4(0);

}

LightComponent::~LightComponent() {
	DrawSystem::get().removeLight(this);
}