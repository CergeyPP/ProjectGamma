#include "CameraComponent.h"
#include "DrawSystem.h"
#include "Converters.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


ComponentManager* CameraComponent::create(GameObject* root, float fov) {

	ObjectPool<CameraComponent> &cameras = DrawSystem::get()->cameraPool;

	auto camera = cameras.instansiate();
	camera->fov_ = fov;

	GLFWwindow* win = DrawSystem::get()->getWindow();
	int width, height;
	glfwGetWindowSize(win, &width, &height);
	camera->resolRatio_ = (float)width / height;

	ComponentManager* manager = camera->createManager(root);

	return manager;

}

glm::mat4 CameraComponent::getProjection() {
	glm::mat4 projection = glm::perspective(fov_ / 2.f, resolRatio_, 0.001f, 100.0f);

	return projection;
}

glm::mat4 CameraComponent::getView() {

	physx::PxMat44 mat = getObject()->transform;
	glm::mat4 transMatrix =	PhysXMat4ToglmMat4(mat);
	glm::mat4 view = glm::lookAt(glm::vec3(transMatrix * glm::vec4(0, 0, 0, 1)),
		/*glm::vec3(transMatrix * glm::vec4(1, 0, 0, 1))*/ glm::vec3(0,0,0),
		glm::vec3(0, 1, 0));

	return view;
}

CameraComponent::CameraComponent() {
	fov_ = 0;
	resolRatio_ = 0;
}

CameraComponent::~CameraComponent() {

}

void CameraComponent::Activate() {
	ObjectPool<CameraComponent> &cameras = DrawSystem::get()->cameraPool;

	/*assert(&cameras.objects[cameras.activeCount] <= this);
	CameraComponent temp = cameras.objects[cameras.activeCount];
	cameras.objects[cameras.activeCount] = *this;
	*this = temp;

	cameras.objects[cameras.activeCount].setManagerPointer(&cameras.objects[cameras.activeCount]);
	this->setManagerPointer(this);
	cameras.activeCount++;*/

	cameras.activate(this);
}

void CameraComponent::Deactivate() {
	ObjectPool<CameraComponent> &cameras = DrawSystem::get()->cameraPool;

	/*assert(&cameras.objects[cameras.activeCount] > this);
	cameras.activeCount--;
	CameraComponent temp = cameras.objects[cameras.activeCount];
	cameras.objects[cameras.activeCount] = *this;
	*this = temp;

	cameras.objects[cameras.activeCount].setManagerPointer(&cameras.objects[cameras.activeCount]);
	this->setManagerPointer(this);*/

	cameras.deactivate(this);
}

void CameraComponent::destroy() {
	ObjectPool<CameraComponent>& cameras = DrawSystem::get()->cameraPool;

	if (isEnabled())
		setEnabled(false);

	cameras.destroy(this);

	Component::destroy();
}

void CameraComponent::onSwap(int newIndex) {
	if (rootManager_ != nullptr) {
		setManagerPointer(& DrawSystem::get()->cameraPool.objects[newIndex]);
	}
}