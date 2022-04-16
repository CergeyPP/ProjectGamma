#include "CameraComponent.h"
#include "DrawSystem.h"
#include "Converters.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

CameraComponent::CameraComponent(GameObject* root) : Component(root) {
	FOV = 0.f;
	DrawSystem::get().addCamera(this);
}

CameraComponent::~CameraComponent()
{
	DrawSystem::get().removeCamera(this);
}
