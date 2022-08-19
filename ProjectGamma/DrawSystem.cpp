#include "DrawSystem.h"
#include "ShaderEnum.h"
#include "Shader.h"
#include <iostream>
#include <assert.h>
#include <glm/gtc/type_ptr.hpp>

void DrawSystem::loadLight()
{
	int lightSize = light_.size();
	glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(int), &lightSize);
	int i = 0;
	for (auto& elem : light_) {

		Light& light = elem->light;
		light.position = glm::vec4(elem->getRoot()->getPos(), 1);
		light.direction = elem->getRoot()->getTransformMatrix() * glm::vec4(1, 0, 0, 0);

		glBufferSubData(GL_UNIFORM_BUFFER, 16 + sizeof(Light) * i, sizeof(Light), &light);

		i++;
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

DrawSystem::DrawSystem() : window_(Window::get()) {

	shader_.resize(ShaderType_Max, Shader());
	shader_[Simplest_Shader].loadVertex("VertexSimple.glsl"); // тут опечатка!
	shader_[Simplest_Shader].loadFragment("FragmentSimple.glsl");
	shader_[Simplest_Shader].linkProgram();

	shader_[Light_Shader].loadVertex("VLightProcessed.glsl");
	shader_[Light_Shader].loadFragment("FLightProcessed.glsl");
	shader_[Light_Shader].linkProgram();

	shader_[Default_Shader].loadVertex("DefaultVertex.glsl");
	shader_[Default_Shader].loadFragment("DefaultFragment.glsl");
	shader_[Default_Shader].linkProgram();

	glUniformBlockBinding(shader_[Light_Shader].getProgram(), glGetUniformBlockIndex(shader_[Light_Shader].getProgram(), "LightBlock"), 1);

	std::cout << "Location of light:" << glGetUniformBlockIndex(shader_[Light_Shader].getProgram(), "LightBlock") << std::endl;

	mainCamera_ = nullptr;



}

void DrawSystem::draw() {

	glm::vec4 ambient = Scene::get().ambientColor;

	if (mainCamera_ == nullptr) return;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	// drawing objects
	glm::mat4 projection = glm::perspective(mainCamera_->FOV / 2.f, window_.getSize().x / window_.getSize().y, 0.1f, 100.f);
	glm::mat4 cameraTransform = mainCamera_->getRoot()->getTransformMatrix();

	glm::vec3 pos = glm::vec3(cameraTransform * glm::vec4(0, 0, 0, 1));

	glm::mat4 view = glm::lookAt(pos/*glm::vec3(4, 3, 2)*/,
		glm::vec3(cameraTransform * glm::vec4(1, 0, 0, 1))/*glm::vec3(0,0,0)*/,
		glm::vec3(0, 1, 0));

	loadLight();

	for (auto& elem : shader_) {
		if (elem.getProgram() > 0x7fffffff) continue;
		glUseProgram(elem.getProgram());
		elem.setUniform("ambientColor", ambient);
		elem.setUniform("Projection", projection);
		elem.setUniform("View", view);
		elem.setUniform("viewPos", pos);
		elem.setUniform("gamma", gamma);
	}

	for (auto& drawable : drawable_) {
		drawable->draw();
	}

	//// end of drawing
	glfwSwapBuffers(window_.getGLFWwindow());
}

void DrawSystem::addCamera(CameraComponent* camera) {
	if (mainCamera_ == nullptr) {
		mainCamera_ = camera;
	}
	camera_.push_back(camera);
}

void DrawSystem::addDrawable(DrawableComponent* drawable)
{
	drawable_.push_back(drawable);
}

void DrawSystem::addLight(LightComponent* light)
{
	light_.push_back(light);
}

void DrawSystem::removeCamera(CameraComponent* camera)
{
	auto camElem = std::find(camera_.begin(), camera_.end(), camera);
	if (camElem < camera_.end()) {
		camera_.erase(camElem);
	}
}

void DrawSystem::removeDrawable(DrawableComponent* drawable)
{
	auto drawElem = std::find(drawable_.begin(), drawable_.end(), drawable);
	if (drawElem < drawable_.end()) {
		drawable_.erase(drawElem);
	}
}

void DrawSystem::removeLight(LightComponent* light)
{
	auto lightElem = std::find(light_.begin(), light_.end(), light);
	if (lightElem < light_.end()) {
		light_.erase(lightElem);
	}
}

GLuint DrawSystem::getTexture(std::string filePath)
{
	if (fileTextures_.count(filePath) == 0) {
		GLuint texID_;
		glGenTextures(1, &texID_);
		glBindTexture(GL_TEXTURE_2D, texID_);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		int width, height;
		unsigned char* image = SOIL_load_image(filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		if (sizeof(image) == 0) {
			printf("File didnt open");
		}
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + int((float)sizeof(image) /width/height/3), width, height, 0, GL_RGB + int((float)sizeof(image) / width / height / 3), GL_UNSIGNED_BYTE, image);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);

		fileTextures_[filePath] = texID_;
	}

	return fileTextures_[filePath];
}

GLuint DrawSystem::getTexture(glm::vec4 color)
{
	if (colorTextures_.count(color) == 0) {
		GLuint texID_;
		glGenTextures(1, &texID_);
		glBindTexture(GL_TEXTURE_2D, texID_);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		unsigned char image[] = { color.r * 255, color.g * 255, color.b * 255, color.a * 255 };

		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + int((float)sizeof(image) /width/height/3), width, height, 0, GL_RGB + int((float)sizeof(image) / width / height / 3), GL_UNSIGNED_BYTE, image);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		colorTextures_[color] = texID_;
	}

	return colorTextures_[color];
}

ConvexMesh* DrawSystem::getMesh(std::string filePath)
{
	if (fileMeshes_.count(filePath)) {
		return fileMeshes_[filePath];
	}

	processFile(filePath);

	std::cout << "fine" << std::endl;
	std::cout << "fine" << std::endl;

	return fileMeshes_[filePath];
}


void DrawSystem::processFile(std::string& filePath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	ConvexMesh* mesh = new ConvexMesh;
	mesh->directory = filePath.substr(0, filePath.find_last_of('/'));

	processNode(mesh, scene->mRootNode, scene);

	fileMeshes_[filePath] = mesh;
}

void DrawSystem::processNode(ConvexMesh* convexMesh, aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		convexMesh->meshes_.push_back(processMesh(convexMesh, mesh, scene));
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		processNode(convexMesh, node->mChildren[i], scene);
	}
}

Mesh* DrawSystem::processMesh(ConvexMesh* esh, aiMesh* aimesh, const aiScene* scene)
{
	Mesh* mesh = new Mesh();
	for (unsigned int i = 0; i < aimesh->mNumVertices; i++)
	{
		glm::vec3 pos(aimesh->mVertices[i].x, aimesh->mVertices[i].y, aimesh->mVertices[i].z);
		glm::vec3 normal(aimesh->mNormals[i].x, aimesh->mNormals[i].y, aimesh->mNormals[i].z);
		glm::vec2 texcoord(0, 0);
		if (aimesh->mTextureCoords[0]) {
			texcoord = glm::vec2(aimesh->mTextureCoords[0][i].x, aimesh->mTextureCoords[0][i].y);
		}
		mesh->vertices.push_back(Vertex(pos, normal, texcoord));
	}

	for (unsigned int i = 0; i < aimesh->mNumFaces; i++)
	{
		aiFace face = aimesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			mesh->indices.push_back(face.mIndices[j]);

	}

	Material* material = new Material(Default_Shader);
	if (aimesh->mMaterialIndex >= 0)
	{
		aiMaterial* mat = scene->mMaterials[aimesh->mMaterialIndex];
		if (!loadMaterialTextures(material, mat, aiTextureType_DIFFUSE, "material.Albedo", esh->directory)) {
			aiColor3D albedo;
			mat->Get(AI_MATKEY_COLOR_DIFFUSE, albedo);
			material->tex2DParam["material.Albedo"] = getTexture(glm::vec4(albedo.r, albedo.g, albedo.b, 1));
		}
		if (!loadMaterialTextures(material, mat, aiTextureType_SPECULAR, "material.Specular", esh->directory)) {
			aiColor3D spec;

			mat->Get(AI_MATKEY_COLOR_SPECULAR, spec);
			material->tex2DParam["material.Specular"] = getTexture(glm::vec4(spec.r, spec.g, spec.b, 1));
		}

		float shininess;
		mat->Get(AI_MATKEY_SHININESS, shininess);
		material->floatParam["material.shininess"] = shininess;

	}
	mesh->material = material;

	return mesh;
}

bool DrawSystem::loadMaterialTextures(Material* material, aiMaterial* mat, aiTextureType type, std::string typeName, std::string& directory)
{
	if (mat->GetTextureCount(type) == 0) return false;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		material->tex2DParam[typeName + std::to_string(i)] = getTexture(directory + "/" + str.C_Str());
		std::cout << typeName + std::to_string(i) << std::endl;
	}
	return true;
}

DrawSystem::~DrawSystem() {

}