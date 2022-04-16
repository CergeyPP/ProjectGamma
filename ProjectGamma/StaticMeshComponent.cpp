#include "StaticMeshComponent.h"
#include "DrawSystem.h"
#include "Converters.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

StaticMeshComponent::StaticMeshComponent(GameObject* root)
	: DrawableComponent(root), material(Material()) {

}

StaticMeshComponent::~StaticMeshComponent() {

}

void StaticMeshComponent::draw() {

	DrawSystem& system = DrawSystem::get();

	Shader& shader = system.shader_[material.shaderProgram];
	glUseProgram(shader.getProgram());

	glm::mat4 model = getRoot()->getTransformMatrix();
	material.mat4Param["Model"] = model;

	material.use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, EBOindicesCount_, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void StaticMeshComponent::setMesh(Mesh mesh)
{
	mesh_ = mesh;
	init(mesh_);
}

