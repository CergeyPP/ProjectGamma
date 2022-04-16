#include "DrawableComponent.h"
#include "DrawSystem.h"

DrawableComponent::DrawableComponent(GameObject* root) : Component(root) {
	VBO = 0;
	EBO = 0;
	VAO = 0;
	EBOindicesCount_ = 0;

    DrawSystem::get().addDrawable(this);
}

DrawableComponent::~DrawableComponent() {

	if (VBO) {
		glDeleteBuffers(1, &VBO);
	}
	if (EBO) {
		glDeleteBuffers(1, &EBO);
	}
	if (VAO) {
		glDeleteVertexArrays(1, &VAO);
	}

    DrawSystem::get().removeDrawable(this);
}

void DrawableComponent::init(Mesh& mesh) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &(mesh.vertices[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), &(mesh.indices[0]), GL_STATIC_DRAW);

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

    EBOindicesCount_ = mesh.indices.size();
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