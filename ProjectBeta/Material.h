#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "ShaderEnum.h"

class Material {
public:

    ShaderType shaderProgram;

    std::map<const char*, bool> boolParam;
    std::map<const char*, int> intParam;
    std::map<const char*, float> floatParam;
    std::map<const char*, glm::vec2> vec2Param;
    std::map<const char*, glm::vec3> vec3Param;
    std::map<const char*, glm::vec4> vec4Param;
    std::map<const char*, glm::mat3> mat3Param;
    std::map<const char*, glm::mat4> mat4Param;
    std::map<const char*, GLuint> tex2DParam;
    std::map<const char*, GLuint> tex3DParam;

    void use();

    Material(ShaderType shader = No_Shader);
    ~Material();
};
