#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "Window.h"
#include "CameraComponent.h"
#include "DrawableComponent.h"

class DrawSystem
{
public:

	static DrawSystem& get() { static DrawSystem system; return system; };

	void draw();

	std::vector<Shader> shader_;

	Window& window_;

	void addCamera(CameraComponent* camera);
	void addDrawable(DrawableComponent* drawable);

private:

	std::vector<CameraComponent*> camera_;
	std::vector<DrawableComponent*> drawable_;
	CameraComponent* mainCamera_;

	DrawSystem();
	~DrawSystem();
};
