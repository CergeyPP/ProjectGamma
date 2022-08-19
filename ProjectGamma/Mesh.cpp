#include "Mesh.h"
#include "DrawSystem.h"

Mesh::Mesh(const Mesh& mesh) {
    vertices = std::vector<Vertex>(mesh.vertices);
    indices = std::vector<GLuint>(mesh.indices);
    EBOindicesCount = mesh.EBOindicesCount;

    VAO = mesh.VAO;
    VBO = mesh.EBO;
    EBO = mesh.EBO;

    material = mesh.material;
}

Mesh::Mesh() {
    EBOindicesCount = 0;
    VAO = 0;
    EBO = 0;
    VBO = 0;
}

Mesh::Mesh(std::vector<Vertex> vertex, std::vector<GLuint> index)
    : vertices(vertex), indices(index) {
    EBOindicesCount = indices.size();
    VAO = 0;
    EBO = 0;
    VBO = 0;
}

Mesh::~Mesh()
{
    if (VBO) {
        glDeleteBuffers(1, &VBO);
    }
    if (EBO) {
        glDeleteBuffers(1, &EBO);
    }
    if (VAO) {
        glDeleteVertexArrays(1, &VAO);
    }
}

void Mesh::draw(glm::mat4 transformMatrix)
{
    DrawSystem& system = DrawSystem::get();

    if (material == nullptr) {
        return;
    }
    Shader& shader = system.shader_[material->shaderProgram];
    glUseProgram(shader.getProgram());

    material->mat4Param["Model"] = transformMatrix;

    material->use();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, EBOindicesCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::init() {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &(vertices[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &(indices[0]), GL_STATIC_DRAW);

    //vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    //vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    EBOindicesCount = indices.size();
}


Mesh createBoxMesh(glm::vec3 size) {

    std::vector<Vertex> vertices = {
        Vertex(glm::vec3(-size.x,-size.y,-size.z) / 2.f, glm::vec3(0, 0,-1), glm::vec2(1, 1)),
        Vertex(glm::vec3(size.x,-size.y,-size.z) / 2.f, glm::vec3(0, 0,-1), glm::vec2(0, 1)),
        Vertex(glm::vec3(-size.x, size.y,-size.z) / 2.f, glm::vec3(0, 0,-1), glm::vec2(1, 0)),

        Vertex(glm::vec3(size.x,-size.y,-size.z) / 2.f, glm::vec3(0, 0,-1), glm::vec2(0, 1)),
        Vertex(glm::vec3(-size.x, size.y,-size.z) / 2.f, glm::vec3(0, 0,-1), glm::vec2(1, 0)),
        Vertex(glm::vec3(size.x, size.y,-size.z) / 2.f, glm::vec3(0, 0,-1), glm::vec2(0, 0)),

        Vertex(glm::vec3(-size.x,-size.y,-size.z) / 2.f, glm::vec3(-1, 0, 0), glm::vec2(0, 1)),
        Vertex(glm::vec3(-size.x,-size.y, size.z) / 2.f, glm::vec3(-1, 0, 0), glm::vec2(1, 1)),
        Vertex(glm::vec3(-size.x, size.y,-size.z) / 2.f, glm::vec3(-1, 0, 0), glm::vec2(0, 0)),

        Vertex(glm::vec3(-size.x, size.y,-size.z) / 2.f, glm::vec3(-1, 0, 0), glm::vec2(0, 0)),
        Vertex(glm::vec3(-size.x,-size.y, size.z) / 2.f, glm::vec3(-1, 0, 0), glm::vec2(1, 1)),
        Vertex(glm::vec3(-size.x, size.y, size.z) / 2.f, glm::vec3(-1, 0, 0), glm::vec2(1, 0)),

        Vertex(glm::vec3(-size.x, size.y,-size.z) / 2.f, glm::vec3(0, 1, 0), glm::vec2(0, 0)),
        Vertex(glm::vec3(size.x, size.y,-size.z) / 2.f, glm::vec3(0, 1, 0), glm::vec2(1, 0)),
        Vertex(glm::vec3(-size.x, size.y, size.z) / 2.f, glm::vec3(0, 1, 0), glm::vec2(0, 1)),

        Vertex(glm::vec3(size.x, size.y,-size.z) / 2.f, glm::vec3(0, 1, 0), glm::vec2(1, 0)),
        Vertex(glm::vec3(-size.x, size.y, size.z) / 2.f, glm::vec3(0, 1, 0), glm::vec2(0, 1)),
        Vertex(glm::vec3(size.x, size.y, size.z) / 2.f, glm::vec3(0, 1, 0), glm::vec2(1, 1)),

        Vertex(glm::vec3(size.x, size.y, size.z) / 2.f, glm::vec3(1, 0, 0), glm::vec2(0, 0)),
        Vertex(glm::vec3(size.x, size.y,-size.z) / 2.f, glm::vec3(1, 0, 0), glm::vec2(1, 0)),
        Vertex(glm::vec3(size.x,-size.y, size.z) / 2.f, glm::vec3(1, 0, 0), glm::vec2(0, 1)),

        Vertex(glm::vec3(size.x,-size.y, size.z) / 2.f, glm::vec3(1, 0, 0), glm::vec2(0, 1)),
        Vertex(glm::vec3(size.x, size.y,-size.z) / 2.f, glm::vec3(1, 0, 0), glm::vec2(1, 0)),
        Vertex(glm::vec3(size.x,-size.y,-size.z) / 2.f, glm::vec3(1, 0, 0), glm::vec2(1, 1)),

        Vertex(glm::vec3(-size.x, size.y, size.z) / 2.f, glm::vec3(0, 0, 1), glm::vec2(0, 0)),
        Vertex(glm::vec3(size.x, size.y, size.z) / 2.f, glm::vec3(0, 0, 1), glm::vec2(1, 0)),
        Vertex(glm::vec3(-size.x,-size.y, size.z) / 2.f, glm::vec3(0, 0, 1), glm::vec2(0, 1)),

        Vertex(glm::vec3(size.x, size.y, size.z) / 2.f, glm::vec3(0, 0, 1), glm::vec2(1, 0)),
        Vertex(glm::vec3(-size.x,-size.y, size.z) / 2.f, glm::vec3(0, 0, 1), glm::vec2(0, 1)),
        Vertex(glm::vec3(size.x,-size.y, size.z) / 2.f, glm::vec3(0, 0, 1), glm::vec2(1, 1)),

        Vertex(glm::vec3(-size.x,-size.y,-size.z) / 2.f, glm::vec3(0,-1, 0), glm::vec2(0, 1)),
        Vertex(glm::vec3(-size.x,-size.y, size.z) / 2.f, glm::vec3(0,-1, 0), glm::vec2(0, 0)),
        Vertex(glm::vec3(size.x,-size.y,-size.z) / 2.f, glm::vec3(0,-1, 0), glm::vec2(1, 1)),

        Vertex(glm::vec3(-size.x,-size.y, size.z) / 2.f, glm::vec3(0,-1, 0), glm::vec2(0, 0)),
        Vertex(glm::vec3(size.x,-size.y,-size.z) / 2.f, glm::vec3(0,-1, 0), glm::vec2(1, 1)),
        Vertex(glm::vec3(size.x,-size.y, size.z) / 2.f, glm::vec3(0,-1, 0), glm::vec2(1, 0)),
    };

    std::vector<unsigned int> indices = {
        2,1,0,
        3,4,5,

        6,7,8,
        9,10,11,

        14,13,12,
        15,16,17,

        20,19,18,
        23,22,21,

        26,25,24,
        27,28,29,

        32,31,30,
        33,34,35,
    };
    Mesh mesh(vertices, indices);
    return mesh;
}