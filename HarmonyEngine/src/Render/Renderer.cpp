#include "Renderer.h"

#include <vector>

// static const size_t MaxQuadCount = 1000;
// static const size_t MaxVertexCount = MaxQuadCount * 4;
// static const size_t MaxIndexCount = MaxQuadCount * 6;

static std::vector<float> vertices = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.0f,  0.5f
};

static std::vector<unsigned int> indices = {
    0, 1, 2
};

static GLuint s_VaoID;
static GLuint s_EboID;

Renderer::~Renderer() {
    OnDestroy();
}

void Renderer::OnCreate() {
    glGenVertexArrays(1, &s_VaoID);
    glBindVertexArray(s_VaoID);

    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], vboID);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*) 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &s_EboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() & sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_Shader = std::make_unique<Shader>("assets/shaders/default.vert.glsl", "assets/shaders/default.frag.glsl");
}

void Renderer::Update(const float& deltaTime) {
    m_Shader->Bind();

    glBindVertexArray(s_VaoID);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EboID);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    m_Shader->Unbind();
}

void Renderer::OnDestroy() {

}