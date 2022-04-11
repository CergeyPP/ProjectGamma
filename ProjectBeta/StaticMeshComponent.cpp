#include "StaticMeshComponent.h"
#include "DrawSystem.h"
#include "Converters.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ComponentManager* StaticMeshComponent::create(GameObject* Parent, Mesh Mesh, Material Material)
{
	auto& meshes = DrawSystem::get()->staticMeshPool;

	StaticMeshComponent* mesh = meshes.instansiate();
	mesh->mesh = Mesh;
	mesh->init(mesh->mesh);
	mesh->material = Material;

	return mesh->createManager(Parent);
}

StaticMeshComponent::StaticMeshComponent()
	: material(material) {

}

StaticMeshComponent::~StaticMeshComponent() {

}

void StaticMeshComponent::onSwap(int newIndex) {
	auto& meshes = DrawSystem::get()->staticMeshPool.objects;

	setManagerPointer(&meshes[newIndex]);
}

void StaticMeshComponent::Activate() {
	auto& meshes = DrawSystem::get()->staticMeshPool;
	meshes.activate(this);
}

void StaticMeshComponent::Deactivate() {
	auto& meshes = DrawSystem::get()->staticMeshPool;
	meshes.deactivate(this);
}

void StaticMeshComponent::draw() {

	DrawSystem* system = DrawSystem::get();

	Shader& shader = system->shader_[material.shaderProgram];
	glUseProgram(shader.getProgram());

	auto physxMat = physx::PxMat44(getObject()->transform);
	glm::mat4 model = PhysXMat4ToglmMat4(physxMat);
	//shader.setUniform("Model", model);
	glm::vec3 color = glm::vec3(1, 0, 1);
	//shader.setUniform("Albedo", color);

	material.mat4Param["Model"] = model;
	material.vec3Param["Albedo"] = color;

	material.use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, EBOindicesCount_, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void StaticMeshComponent::destroy() {
	auto& meshes = DrawSystem::get()->staticMeshPool;

	if (isEnabled())
		setEnabled(false);

	meshes.destroy(this);

	Component::destroy();
}
