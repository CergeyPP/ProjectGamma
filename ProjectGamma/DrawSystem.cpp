#include "DrawSystem.h"
#include "ShaderEnum.h"
#include "Shader.h"
#include <iostream>
#include <assert.h>
#include <glm/gtc/type_ptr.hpp>


void DrawSystem::loadLight(Shader& shader)
{
	shader.setUniform("lightCount", (int)light_.size());
	int i = 0;
	for (auto& elem : light_) {
		const std::string uniformName = "light[" + std::to_string(i) + "]";
		glm::vec3 position = elem->getRoot()->getPos();
		glm::vec3 direction = elem->getRoot()->getTransformMatrix() * glm::vec4(1, 0, 0, 0);
		int type = (int)elem->type;
		float cutoff = elem->cutoff;
		float linear = elem->linear;
		float quadratic = elem->quadratic;
		glm::vec3 diffuse = elem->diffuse;
		glm::vec3 specular = elem->specular;

		shader.setUniform(uniformName + ".type", type);
		shader.setUniform(uniformName + ".position", position);
		shader.setUniform(uniformName + ".direction", direction);
		shader.setUniform(uniformName + ".cutoff", cutoff);
		shader.setUniform(uniformName + ".linear", linear);
		shader.setUniform(uniformName + ".quadratic", quadratic);
		shader.setUniform(uniformName + ".diffuse", diffuse);
		shader.setUniform(uniformName + ".specular", specular);
	}
}

DrawSystem::DrawSystem() : window_(Window::get()) {

	shader_.resize(ShaderType_Max, Shader());
	shader_[Simplest_Shader].loadVertex("VertexSimple.glsl"); // тут опечатка!
	shader_[Simplest_Shader].loadFragment("FragmentSimple.glsl");
	shader_[Simplest_Shader].linkProgram();

	shader_[Light_Shader].loadVertex("VLightProcessed.glsl"); 
	shader_[Light_Shader].loadFragment("FLightProcessed.glsl");
	shader_[Light_Shader].linkProgram();

	//std::cout << "Location of light:" << glGetUniformLocation(shader_[Light_Shader].getProgram(), "light[0]") << std::endl;

	mainCamera_ = nullptr;
}

void DrawSystem::draw() {

	glm::vec4 ambient = Scene::get().ambientColor;

	if (mainCamera_ == nullptr) return;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	// drawing objects
	glm::mat4 projection = glm::perspective(mainCamera_->FOV/2.f, window_.getSize().x / window_.getSize().y, 0.1f, 100.f);
	glm::mat4 cameraTransform = mainCamera_->getRoot()->getTransformMatrix();

	glm::vec3 pos = glm::vec3(cameraTransform * glm::vec4(0, 0, 0, 1));

	glm::mat4 view = glm::lookAt(pos/*glm::vec3(4, 3, 2)*/,
		glm::vec3(cameraTransform * glm::vec4(1, 0, 0, 1))/*glm::vec3(0,0,0)*/,
		glm::vec3(0, 1, 0));

	for (auto& elem : shader_) {
		if (elem.getProgram() > 0x7fffffff) continue;
		glUseProgram(elem.getProgram());
		elem.setUniform("ambientColor", ambient);
		elem.setUniform("Projection", projection);
		elem.setUniform("View", view);
		elem.setUniform("viewPos", pos);
		loadLight(elem);
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

void DrawSystem::addLight(LightComponent* light)
{
	light_.push_back(light);
}

void DrawSystem::removeCamera(CameraComponent* camera)
{
	auto camElem = std::find(camera_.begin(), camera_.end(), camera);
	if (camElem < camera_.end()) {
		camera_.erase(camElem);
	}
}

void DrawSystem::removeDrawable(DrawableComponent* drawable)
{
	auto drawElem = std::find(drawable_.begin(), drawable_.end(), drawable);
	if (drawElem < drawable_.end()) {
		drawable_.erase(drawElem);
	}
}

void DrawSystem::removeLight(LightComponent* light)
{
	auto lightElem = std::find(light_.begin(), light_.end(), light);
	if (lightElem < light_.end()) {
		light_.erase(lightElem);
	}
}

DrawSystem::~DrawSystem() {
	
}