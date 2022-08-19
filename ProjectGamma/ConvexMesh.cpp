#include "ConvexMesh.h"


void ConvexMesh::init() {
	for (auto elem : meshes_) {
		elem->init();
	}
}

void ConvexMesh::draw(glm::mat4 transformMatrix)
{
	Mesh::draw(transformMatrix);
	for (auto elem : meshes_) {
		elem->draw(transformMatrix);
	}
}


ConvexMesh::ConvexMesh()
{
}

ConvexMesh::ConvexMesh(ConvexMesh* mesh)
	: Mesh(*mesh)
{
	for (int i = 0; i < mesh->meshes_.size(); i++) {
		if (dynamic_cast<ConvexMesh*>(mesh->meshes_[i]))
			meshes_.push_back(new ConvexMesh((ConvexMesh*)(mesh->meshes_[i])));
		else meshes_.push_back(new Mesh(*(mesh->meshes_[i])));
	}
}


ConvexMesh::~ConvexMesh()
{
	for (auto elem : meshes_) {
		delete elem;
	}
}
