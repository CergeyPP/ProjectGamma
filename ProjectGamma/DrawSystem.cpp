#include "DrawSystem.h"
#include "ShaderEnum.h"
#include "Shader.h"
#include <iostream>
#include <assert.h>
#include <glm/gtc/type_ptr.hpp>


DrawSystem::DrawSystem() : window_(Window::get()) {

	shader_.resize(ShaderType_Max, Shader());
	shader_[Simplest_Shader].loadVertex("VertexSimpl.glsl"); // тут опечатка!
	shader_[Simplest_Shader].loadFragment("FragmentSimple.glsl");
	shader_[Simplest_Shader].linkProgram();

	mainCamera_ = nullptr;
}

void DrawSystem::draw() {

	if (mainCamera_ == nullptr) return;

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	// drawing objects
	glm::mat4 projection = glm::perspective(mainCamera_->FOV/2.f, window_.getSize().x / window_.getSize().y, 0.1f, 100.f);
	glm::mat4 cameraTransform = mainCamera_->getRoot()->getTransformMatrix();


	glm::mat4 view = glm::lookAt(/*cameraTransform * glm::vec4(0, 0, 0, 1)*/glm::vec3(4, 3, 2),
		/*glm::vec3(cameraTransform * glm::vec4(1, 0, 0, 1))*/glm::vec3(0,0,0),
		glm::vec3(0, 1, 0));

	for (auto& elem : shader_) {
		if (elem.getProgram() > 0x7fffffff) continue;
		glUseProgram(elem.getProgram());
		elem.setUniform("Projection", projection);
		elem.setUniform("View", view);
	}

	for (auto& drawable : drawable_) {
		drawable->draw();
	}

	//// end of drawing
	glfwSwapBuffers(window_.getGLFWwindow());
}

void DrawSystem::addCamera(CameraComponent* camera) {
	if (mainCamera_ == nullptr) {
		mainCamera_ = camera;
	}
	camera_.push_back(camera);
}

void DrawSystem::addDrawable(DrawableComponent* drawable)
{
	drawable_.push_back(drawable);
}

DrawSystem::~DrawSystem() {
	
}