#include "Material.h"
#include "DrawSystem.h"
#include <glm/gtc/type_ptr.hpp>

void Material::use()
{
    Shader& shader = DrawSystem::get()->shader_[shaderProgram];

    glUseProgram(shader.getProgram());

    for (auto &elem : boolParam) {
        shader.setUniform(elem.first, elem.second);
    }
    for (auto& elem : floatParam) {
        shader.setUniform(elem.first, elem.second);
    }
    for (auto& elem : intParam) {
        shader.setUniform(elem.first, elem.second);
    }
    for (auto& elem : vec3Param) {
        shader.setUniform(elem.first, elem.second);
    }
    for (auto& elem : vec4Param) {
        shader.setUniform(elem.first, elem.second);
    }
    for (auto& elem : vec2Param) {
        shader.setUniform(elem.first, elem.second);
    }
    for (auto& elem : mat3Param) {
        shader.setUniform(elem.first, elem.second);
    }
    for (auto& elem : mat4Param) {
        shader.setUniform(elem.first, elem.second);
    }
    for (auto& elem : tex2DParam) {
        shader.setTexture2D(elem.first, elem.second);
    }
    for (auto& elem : tex3DParam) {
        shader.setTexture3D(elem.first, elem.second);
    }
}

Material::Material(ShaderType shader) {
    shaderProgram = shader;
}
Material::~Material() {

   
}