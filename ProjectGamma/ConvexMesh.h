#pragma once
#include "Mesh.h"

class ConvexMesh : public Mesh {
public:

	ConvexMesh();
	ConvexMesh(ConvexMesh* mesh);

	~ConvexMesh() override;

	void init() override;

	void draw(glm::mat4 transformMatrix) override;

	bool isConvex() override { return true; }

	std::string directory;

	std::vector<Mesh*> meshes_;
};