#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <glm/glm.hpp>

class Shader {
public:

	void loadVertex(const char* shaderPath);
	void loadFragment(const char* shaderPath);
	void loadGeometry(const char* shaderPath);

	void linkProgram();

	GLuint getProgram();
	void releaseProgram();

	void setUniform(const char* name, bool& value);
	void setUniform(const char* name, int& value);
	void setUniform(const char* name, float& value);
	void setUniform(const char* name, glm::vec3& value);
	void setUniform(const char* name, glm::vec2& value);
	void setUniform(const char* name, glm::vec4& value);
	void setUniform(const char* name, glm::mat3& value);
	void setUniform(const char* name, glm::mat4& value);
	void setTexture3D(const char* name, GLuint& value);
	void setTexture2D(const char* name, GLuint& value);


private:

	struct TextureUniform {
		int textureIndex;
		GLuint offset;
	};

	GLint program_ = -1;
	std::map<const char*, GLuint> uniformOffset_;
	std::map<const char*, TextureUniform> textureUniformOffset_;

	GLint vertexShaderID_ = -1;
	GLint fragmentShaderID_ = -1;
	GLint geometryShaderID_ = -1;
	

	int textureCount = 0;
};