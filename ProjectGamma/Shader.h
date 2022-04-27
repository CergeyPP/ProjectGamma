#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <glm/glm.hpp>
#include <SOIL/SOIL.h>

class Shader {
public:

	void loadVertex(const std::string shaderPath);
	void loadFragment(const std::string shaderPath);
	void loadGeometry(const std::string shaderPath);

	void linkProgram();

	GLuint getProgram();
	void releaseProgram();

	void setUniform(const std::string name, bool value);
	void setUniform(const std::string name, int value);
	void setUniform(const std::string name, float value);
	void setUniform(const std::string name, glm::vec3& value);
	void setUniform(const std::string name, glm::vec2& value);
	void setUniform(const std::string name, glm::vec4& value);
	void setUniform(const std::string name, glm::mat3& value);
	void setUniform(const std::string name, glm::mat4& value);
	void setTexture3D(const std::string name, GLuint value);
	void setTexture2D(const std::string name, GLuint value);


private:

	struct TextureUniform {
		int textureIndex;
		GLuint offset;
	};

	GLint program_ = -1;
	std::map<const std::string, GLuint> uniformOffset_;
	std::map<const std::string, TextureUniform> textureUniformOffset_;

	GLint vertexShaderID_ = -1;
	GLint fragmentShaderID_ = -1;
	GLint geometryShaderID_ = -1;
	
	int textureCount = 0;
};

