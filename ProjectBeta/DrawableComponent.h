#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    unsigned int EBOindicesCount;
    Mesh(const Mesh& mesh) {
        vertices = std::vector<Vertex>(mesh.vertices);
        indices = std::vector<GLuint>(mesh.indices);
        EBOindicesCount = mesh.EBOindicesCount;
    }
    Mesh() {

    }
    Mesh(std::vector<Vertex> vertex, std::vector<GLuint> index)
        : vertices(vertex), indices(index) {
        EBOindicesCount = indices.size();
    }
};

class DrawableComponent :
    public Component
{
public:

    DrawableComponent();
    ~DrawableComponent() override;

    virtual void draw() = 0;

    void destroy() override;

protected:

    void init(Mesh mesh);

    ComponentManager* createManager(GameObject* root);

    GLuint VBO;
    GLuint EBO;
    GLuint VAO;

    unsigned int EBOindicesCount_;
};

Mesh createBoxMesh(glm::vec3 size);