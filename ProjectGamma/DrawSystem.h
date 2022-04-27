#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "Window.h"
#include "CameraComponent.h"
#include "DrawableComponent.h"
#include "LightComponent.h"

#define LIGHTS_MAX 100

class DrawSystem
{
public:

	static DrawSystem& get() { static DrawSystem system; return system; };

	void draw();

	std::vector<Shader> shader_;

	Window& window_;

	void addCamera(CameraComponent* camera);
	void addDrawable(DrawableComponent* drawable);
	void addLight(LightComponent* light);

	void removeCamera(CameraComponent* camera);
	void removeDrawable(DrawableComponent* drawable);
	void removeLight(LightComponent* light);


	GLuint getTexture(std::string filePath);
	GLuint getTexture(glm::vec4 color);

private:

	std::vector<CameraComponent*> camera_;
	std::vector<DrawableComponent*> drawable_;
	std::vector<LightComponent*> light_;
	CameraComponent* mainCamera_;

	void loadLight();

	GLuint lightUBO;

	struct vec4LessComparator {
		bool operator()(const glm::vec4& first, const glm::vec4& second) const {
			return glm::length(first) < glm::length(second) && (first.x < second.x);
		}
	};

	std::map<std::string, GLuint> fileTextures_;
	std::map < glm::vec4, GLuint, vec4LessComparator> colorTextures_;

	DrawSystem();
	~DrawSystem();
};
