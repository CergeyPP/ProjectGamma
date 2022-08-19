#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "Window.h"
#include "CameraComponent.h"

#include "LightComponent.h"
#include "Material.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define LIGHTS_MAX 100

class Mesh;
class ConvexMesh;
class DrawableComponent;

class DrawSystem
{
public:

	static DrawSystem& get() { static DrawSystem system; return system; };

	void draw();

	std::vector<Shader> shader_;

	Window& window_;

	void addCamera(CameraComponent* camera);
	void addDrawable(DrawableComponent* drawable);
	void addLight(LightComponent* light);

	void removeCamera(CameraComponent* camera);
	void removeDrawable(DrawableComponent* drawable);
	void removeLight(LightComponent* light);

	GLuint getTexture(std::string filePath);
	GLuint getTexture(glm::vec4 color);

	ConvexMesh* getMesh(std::string filePath);

	float gamma = 2.2;

private:

	std::vector<CameraComponent*> camera_;
	std::vector<DrawableComponent*> drawable_;
	std::vector<LightComponent*> light_;
	CameraComponent* mainCamera_;

	void processFile(std::string& filePath);
	void processNode(ConvexMesh* convexMesh, aiNode* node, const aiScene* scene);
	Mesh* processMesh(ConvexMesh* mesh, aiMesh* aimesh, const aiScene* scene);

	bool loadMaterialTextures(Material* material, aiMaterial* mat, aiTextureType type, std::string typeName, std::string& directory);

	void loadLight();

	GLuint lightUBO;

	struct vec4LessComparator {
		bool operator()(const glm::vec4& first, const glm::vec4& second) const {
			return glm::length(first) < glm::length(second) && (first.x < second.x);
		}
	};

	std::map<std::string, GLuint> fileTextures_;
	std::map < glm::vec4, GLuint, vec4LessComparator> colorTextures_;
	std::map<std::string, ConvexMesh*> fileMeshes_;

	DrawSystem();
	~DrawSystem();
};

#include "ConvexMesh.h"
#include "DrawableComponent.h"