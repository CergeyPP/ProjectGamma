#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "PxPhysicsAPI.h"
#include <functional>
#include <stdio.h>
#include "DrawSystem.h"
#include "Window.h"
#include "Input.h"
#include "Scene.h"

using namespace physx;

class TestEventHandler : public IEventable {
public:

	void onEvent(Event& event) override {
		Window& window = Window::get();
		if (event.getType() == EventType::KEY_PRESSED_EVENT) {
			KeyEvent& keyEvent = (KeyEvent&)event;
			if (keyEvent.button == GLFW_KEY_ESCAPE) {
				glfwSetWindowShouldClose(window.getGLFWwindow(), true);
			}
		}
		std::cout << (int)event.getType() << std::endl;
	}
	TestEventHandler(EventDispatcher* dispatch)
		: IEventable(dispatch) {
	}
	~TestEventHandler() override {

	}

private:
};

int main() {

	setlocale(LC_ALL, "Ru");

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	DrawSystem& drawSystem = DrawSystem::get();
	glfwPollEvents();
	Input& input = Input::get();
	Scene& scene = Scene::get();
	scene.load();

	//TestEventHandler handler(&window.dispatcher);

	float currentTime = glfwGetTime();

	while (!glfwWindowShouldClose(drawSystem.window_.getGLFWwindow())) {

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

		scene.update(deltaTime);

		glfwPollEvents();

		drawSystem.draw();

		//glfwSwapBuffers(window.getGLFWwindow());

		//meshComp->draw();
	}

	glfwTerminate();

	scene.load("");

	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	//_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	//_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	//_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	//_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	//_CrtDumpMemoryLeaks();

	system("pause");

	return 0;
}