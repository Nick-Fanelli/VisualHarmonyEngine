#include "Renderer.h"

// static const int MaxQuadCount = 1000;
// static const int MaxVertexCount = MaxQuadCount * 4; // 4 vertices per quad
// static const int MaxIndexCount = MaxQuadCount * 6; // 6 indices per quad

struct Vertex {

    glm::vec2 Position;
    glm::vec4 Color;
    
};

// Test Triangle Drawing Code
static Vertex vertices[] {
    { { -0.5f, 0.5f }, { 1, 0, 0, 1 } },
    { { -0.5f, -0.5f }, { 0, 1, 0, 1 } },
    { { 0.5f, -0.5f }, { 0, 0, 1, 1 } },
    { { 0.5f, 0.5f }, { 1, 0, 1, 1 } }
};

static uint32_t indices[] = { 
    0, 1, 2, 2, 3, 0,
};

struct RenderData {

    GLuint VaoID;
    GLuint VboID;
    GLuint EboID;

};

static RenderData s_Data;

void Renderer::OnCreate() {
    s_Data = RenderData();

    m_Shader = std::make_unique<Shader>("assets/shaders/default.vert.glsl", "assets/shaders/default.frag.glsl");

    // Bind the VAO
    glGenVertexArrays(1, &s_Data.VaoID);
    glBindVertexArray(s_Data.VaoID);

    // Bind the Verticies
    glGenBuffers(1, &s_Data.VboID);
    glBindBuffer(GL_ARRAY_BUFFER, s_Data.VboID); // Bind Vertex Buffer

    // Push the data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, Position));
    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, Color));

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind Buffer

    // Bind the indices
    glGenBuffers(1, &s_Data.EboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.EboID); // Bind Indicies Buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind Buffer
    glBindVertexArray(0);
}

void Renderer::Update(const float& deltaTime) {
    m_Shader->Bind();

    glBindVertexArray(s_Data.VaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.EboID);

    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    m_Shader->Unbind();
}

void Renderer::OnDestroy() {

}