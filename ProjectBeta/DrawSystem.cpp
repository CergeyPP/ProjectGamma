#include "DrawSystem.h"
#include "ShaderEnum.h"
#include "Shader.h"
#include <iostream>
#include <assert.h>
#include <glm/gtc/type_ptr.hpp>

bool DrawSystem::instanced_ = false;
DrawSystem* DrawSystem::system_ = nullptr;

DrawSystem* DrawSystem::get() {

	if (!instanced_) {

		system_ = new DrawSystem();
		instanced_ = true;
	}

	return system_;
}

void DrawSystem::setupCamera(CameraComponent& camera) {

	glm::mat4 view = camera.getView();
	glm::mat4 projection = camera.getProjection();

	for (auto &elem : shader_) {

		if (elem.getProgram() > 0) {

			glUseProgram(elem.getProgram());

			elem.setUniform("View", view);
			elem.setUniform("Projection", projection);

			/*GLuint viewLoc = getShaderUniformLoc(elem, "View");
			if (viewLoc < 0) std::cout << "Not Found!\n";
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			GLuint projectionLoc = getShaderUniformLoc(elem, "Projection");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));*/
		}
	}
}

DrawSystem::DrawSystem() : cameraPool(MAX_CAMERAS) , staticMeshPool(MAX_OBJECTS) {

	assert(!instanced_);

	
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		window_ = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game", nullptr, nullptr);
		if (!window_) {
			std::cout << "Failed to create window" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(window_);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			std::cout << glewGetErrorString(GLEW_VERSION) << std::endl;
		}

		int width, height;
		glfwGetFramebufferSize(window_, &width, &height);
		glViewport(0, 0, width, height);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);
	

	shader_.resize(ShaderType_Max, Shader());
	shader_[Simplest_Shader].loadVertex("VertexSimple.glsl");
	shader_[Simplest_Shader].loadFragment("FragmentSimple.glsl");
	shader_[Simplest_Shader].linkProgram();
	//shader_[Simplest_Shader].program = loadShader("VertexSimple.glsl", "FragmentSimple.glsl");
}

void DrawSystem::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	// drawing objects
	CameraComponent* camera = cameraPool.getAll();
	int cameraActives = cameraPool.getActiveCount();

	StaticMeshComponent* meshes = staticMeshPool.getAll();
	int meshActives = staticMeshPool.getActiveCount();

	for (int current = 0; current < cameraActives; current++) {
		setupCamera(camera[current]);

		for (int meshIndex = 0; meshIndex < meshActives; meshIndex++) {
			meshes[meshIndex].draw();
		}
	}

	// end of drawing
	glfwSwapBuffers(window_);
}

DrawSystem::~DrawSystem() {
	instanced_ = false;
	system_ = nullptr;

	glfwDestroyWindow(window_);
}