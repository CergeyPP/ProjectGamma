#include "StaticMeshComponent.h"
#include "ConvexMesh.h"
#include "DrawSystem.h"
#include "Converters.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


StaticMeshComponent::StaticMeshComponent(GameObject* root)
	: DrawableComponent(root) {

}

StaticMeshComponent::~StaticMeshComponent() {

}

void StaticMeshComponent::draw() {

	mesh->draw(getRoot()->getTransformMatrix());
}

void StaticMeshComponent::setMesh(Mesh* mesh_)
{

	if (mesh_->isConvex()) {
		mesh = new ConvexMesh((ConvexMesh*)mesh_);
	}
	else mesh = new Mesh(*mesh_);
	mesh->init();
}

