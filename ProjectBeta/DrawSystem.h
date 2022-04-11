#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>


//#include "LightPool.h"
#include "ObjectPool.h"
#include "Shader.h"
#include "Defines.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

class CameraComponent;
class StaticMeshComponent;

class DrawSystem
{
public:

	static DrawSystem* get();

	~DrawSystem();

	GLFWwindow* getWindow() { return window_; }

	void draw();

	ObjectPool<CameraComponent> cameraPool;
	ObjectPool<StaticMeshComponent> staticMeshPool;

	std::vector<Shader> shader_;

private:

	DrawSystem();

	GLFWwindow* window_;

	static bool instanced_;
	static DrawSystem* system_;

	void setupCamera(CameraComponent& camera);

};

#include "CameraComponent.h"
#include "StaticMeshComponent.h"