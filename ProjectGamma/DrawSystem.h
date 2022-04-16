#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "Window.h"
#include "CameraComponent.h"
#include "DrawableComponent.h"
#include "LightComponent.h"

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

private:

	std::vector<CameraComponent*> camera_;
	std::vector<DrawableComponent*> drawable_;
	std::vector<LightComponent*> light_;
	CameraComponent* mainCamera_;

	void loadLight(Shader& shader);

	DrawSystem();
	~DrawSystem();
};
