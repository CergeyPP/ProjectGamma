#include "DrawSystem.h"
#include "ShaderEnum.h"
#include "Shader.h"
#include <iostream>
#include <assert.h>
#include <glm/gtc/type_ptr.hpp>


void DrawSystem::loadLight()
{
	//shader.setUniform("lightCount", (int)light_.size());
	int lightSize = light_.size();
	glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(int), &lightSize);
	int i = 0;
	for (auto& elem : light_) {

		//const std::string uniformName = "light[" + std::to_string(i) + "]";
		Light& light = elem->light;
		light.position = glm::vec4(elem->getRoot()->getPos(), 1);
		light.direction = elem->getRoot()->getTransformMatrix() * glm::vec4(1, 0, 0, 0);


		/*int type = (int)light.type;
		float cutoff = light.cutoff;
		float linear = light.linear;
		float quadratic = light.quadratic;
		glm::vec3 diffuse = light.diffuse;
		glm::vec3 specular = light.specular;*/

		glBufferSubData(GL_UNIFORM_BUFFER, 16 + sizeof(Light) * i, sizeof(Light), &light);

		/*shader.setUniform(uniformName + ".type", type);
		shader.setUniform(uniformName + ".position", position);
		shader.setUniform(uniformName + ".direction", direction);
		shader.setUniform(uniformName + ".cutoff", cutoff);
		shader.setUniform(uniformName + ".linear", linear);
		shader.setUniform(uniformName + ".quadratic", quadratic);
		shader.setUniform(uniformName + ".diffuse", diffuse);
		shader.setUniform(uniformName + ".specular", specular);*/

		i++;
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

DrawSystem::DrawSystem() : window_(Window::get()) {

	shader_.resize(ShaderType_Max, Shader());
	shader_[Simplest_Shader].loadVertex("VertexSimple.glsl"); // тут опечатка!
	shader_[Simplest_Shader].loadFragment("FragmentSimple.glsl");
	shader_[Simplest_Shader].linkProgram();

	shader_[Light_Shader].loadVertex("VLightProcessed.glsl"); 
	shader_[Light_Shader].loadFragment("FLightProcessed.glsl");
	shader_[Light_Shader].linkProgram();


	std::cout << glGetUniformBlockIndex(shader_[Light_Shader].getProgram(), "LightBlock") << std::endl;
	//glUniformBlockBinding(shader_[Light_Shader].getProgram(), glGetUniformBlockIndex(shader_[Light_Shader].getProgram(), "LightBlock"), 1);

	//std::cout << "Location of light:" << glGetUniformLocation(shader_[Light_Shader].getProgram(), "light[0]") << std::endl;

	mainCamera_ = nullptr;

	glGenBuffers(1, &lightUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
	glBufferData(GL_UNIFORM_BUFFER, LIGHTS_MAX * sizeof(Light) + 16, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, lightUBO);

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

	loadLight();

	for (auto& elem : shader_) {
		if (elem.getProgram() > 0x7fffffff) continue;
		glUseProgram(elem.getProgram());
		elem.setUniform("ambientColor", ambient);
		elem.setUniform("Projection", projection);
		elem.setUniform("View", view);
		elem.setUniform("viewPos", pos);
		
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

GLuint DrawSystem::getTexture(std::string filePath)
{
	if (fileTextures_.count(filePath) == 0) {
		GLuint texID_;
		glGenTextures(1, &texID_);
		glBindTexture(GL_TEXTURE_2D, texID_);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		int width, height;
		unsigned char* image = SOIL_load_image(filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		if (sizeof(image) == 0) {
			printf("File didnt open");
		}
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + int((float)sizeof(image) /width/height/3), width, height, 0, GL_RGB + int((float)sizeof(image) / width / height / 3), GL_UNSIGNED_BYTE, image);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);

		fileTextures_[filePath] = texID_;
	}

	return fileTextures_[filePath];
}

GLuint DrawSystem::getTexture(glm::vec4 color)
{
	if (colorTextures_.count(color) == 0) {
		GLuint texID_;
		glGenTextures(1, &texID_);
		glBindTexture(GL_TEXTURE_2D, texID_);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		unsigned char image[] = { color.r * 255, color.g * 255, color.b * 255, color.a * 255 };

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + int((float)sizeof(image) /width/height/3), width, height, 0, GL_RGB + int((float)sizeof(image) / width / height / 3), GL_UNSIGNED_BYTE, image);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		colorTextures_[color] = texID_;
	}

	return colorTextures_[color];
}

DrawSystem::~DrawSystem() {
	
}