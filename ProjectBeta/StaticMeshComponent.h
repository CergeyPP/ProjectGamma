#pragma once
#include "DrawableComponent.h"
#include "Material.h"

class StaticMeshComponent 
	: public DrawableComponent
{
public:

	static ComponentManager* create(GameObject* parent, Mesh mesh, Material material = Material());

	StaticMeshComponent();
	~StaticMeshComponent() override;

	void onSwap(int newIndex) override;
	void Activate() override;
	void Deactivate() override;

	void draw() override;

	void destroy() override;

	Material material;

private:

	Mesh mesh;

	friend ObjectPool<StaticMeshComponent>;
};

