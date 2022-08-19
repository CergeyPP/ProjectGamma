#pragma once
#include "DrawableComponent.h"
#include "Material.h"

class StaticMeshComponent
	: public DrawableComponent
{
public:

	void draw() override;

	void setMesh(Mesh* mesh);

private:

	StaticMeshComponent(GameObject* root);
	~StaticMeshComponent() override;



	friend GameObject;
};

