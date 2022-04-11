#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "PxPhysicsAPI.h"
#include <functional>

#include "Window.h"

using namespace physx;



int main() {

	setlocale(LC_ALL, "Ru");

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//DrawSystem *drawSystem = DrawSystem::get();
	//PhysicSystem* physicSystem = PhysicSystem::get();
	//InputSystem* inputSystem = InputSystem::get();

	//World *world = World::get();
	//world->load();

	//glfwSetMouseButtonCallback(drawSystem->getWindow(), Input::mouseButtonCallback);
	//glfwSetKeyCallback(drawSystem->getWindow(), Input::keyCallback);
	//glfwSetCursorPosCallback(drawSystem->getWindow(), Input::mouseCursorCallback);

	//glClearColor(0.3, 0.3, 0.3, 1.f);

	Window& window = Window::get();

	float currentTime = glfwGetTime();

	while (!glfwWindowShouldClose(window.getGLFWwindow())) {

		float time = glfwGetTime();
		float deltaTime = time - currentTime;
		currentTime = time;

		//currentTime = glfwGetTime();
		//nbFrames++;
		//if (currentTime - LastTime >= 1.0) { // If last prinf() was more than 1 sec ago
		//	// printf and reset timer
		//	printf("%f ms/frame\n", 1000.0 / double(nbFrames));
		//	nbFrames = 0;
		//	LastTime += 1.0;
		//}

		//std::cout << deltaTime << std::endl;

		//world->update(deltaTime);

		glfwPollEvents();

		//drawSystem->draw();

		//meshComp->draw();
	}

	glfwTerminate();

	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	//_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	//_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	//_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	//_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	//_CrtDumpMemoryLeaks();

	//system("pause");

	return 0;
}