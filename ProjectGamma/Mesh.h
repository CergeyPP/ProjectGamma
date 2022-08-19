#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Material.h"

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoords;

    Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texCoords) {
        this->pos = pos;
        this->normal = normal;
        this->texCoords = texCoords;
    }
};

class Mesh {
public:

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    unsigned int EBOindicesCount = 0;

    Mesh(const Mesh& mesh);
    Mesh();
    Mesh(std::vector<Vertex> vertex, std::vector<GLuint> index);

    virtual ~Mesh();

    Material* material = nullptr;

    virtual void init();

    virtual void draw(glm::mat4 transformMatrix);

    virtual bool isConvex() { return false; }

private:

    GLuint VBO;
    GLuint EBO;
    GLuint VAO;
};

Mesh createBoxMesh(glm::vec3 size);