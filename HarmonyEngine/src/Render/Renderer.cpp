#include "Renderer.h"

#include <iostream>

#include "../Scene/Scene.h"

static const size_t MaxQuadCount = 1000;
static const size_t MaxVertexCount = MaxQuadCount * 4;
static const size_t MaxIndexCount = MaxQuadCount * 6;

// Test Triangle Drawing Code
// static Vertex vertices[] {
//     { { -1.5f, 0.5f }, { 1, 0, 0, 1 } },
//     { { -1.5f, -0.5f }, { 0, 1, 0, 1 } },
//     { { -0.5f, -0.5f }, { 0, 0, 1, 1 } },
//     { { -0.5f, 0.5f }, { 1, 0, 1, 1 } },

//     { { 1.5f, 0.5f }, { 0, 1, 0, 1 } },
//     { { 1.5f, -0.5f }, { 1, 0, 0, 1 } },
//     { { 0.5f, -0.5f }, { 0, 0, 1, 1 } },
//     { { 0.5f, 0.5f }, { 0, 1, 1, 1 } },
// };

// static uint32_t indices[] = { 
//     0, 1, 2, 2, 3, 0,
//     4, 5, 6, 6, 7, 4
// };

struct RenderData {

    GLuint VaoID = 0;
    GLuint VboID = 0;
    GLuint EboID = 0;

    uint32_t IndexCount = 0;

    Vertex* Vertices = nullptr;
    Vertex* VertexPtr = nullptr;

};

static RenderData s_Data;

void Renderer::OnCreate(OrthographicCamera* camera) {
    if(s_Data.Vertices != nullptr) {
        Log::Error("Vertices array was not nullptr, exiting Renderer::OnCreate()");
        return;
    }

    s_Data = RenderData();
    s_Data.Vertices = new Vertex[MaxVertexCount];
    s_Data.VertexPtr = s_Data.Vertices;

    // s_Data.Vertices[0] = vertices[0];
    // s_Data.Vertices[1] = vertices[1];
    // s_Data.Vertices[2] = vertices[2];
    // s_Data.Vertices[3] = vertices[3];

    // s_Data.IndexCount = 6;

    m_Camera = camera;
    m_Shader = std::make_unique<Shader>("assets/shaders/default.vert.glsl", "assets/shaders/default.frag.glsl");

    // Bind the VAO
    glGenVertexArrays(1, &s_Data.VaoID);
    glBindVertexArray(s_Data.VaoID);

    // Bind the Verticies
    glGenBuffers(1, &s_Data.VboID);
    glBindBuffer(GL_ARRAY_BUFFER, s_Data.VboID); // Bind Vertex Buffer

    // Push the data
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MaxVertexCount, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, Position));
    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, Color));

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind Buffer

    uint32_t indices[MaxIndexCount];
    uint32_t offset = 0;

    for(size_t i = 0; i < MaxIndexCount; i += 6) {
        // First Triangle
        indices[i]     = offset;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        // Second Triangle
        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset;

        offset += 4;
    }

    // Bind the indices
    glGenBuffers(1, &s_Data.EboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.EboID); // Bind Indicies Buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind Buffer
    glBindVertexArray(0);
}

void Renderer::Update(const float& deltaTime) {

    if(m_ShouldUpdateVertexData) {
        Renderer::UpdateBatchVertexData();
        m_ShouldUpdateVertexData = false;
    }

    Renderer::Render();
}

void Renderer::UpdateBatchVertexData() {
    Log::Info("Updating Batch Vertex Data");

    GLsizeiptr size = (uint8_t*) s_Data.VertexPtr - (uint8_t*) s_Data.Vertices;

    glBindBuffer(GL_ARRAY_BUFFER, s_Data.VboID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Data.Vertices);
}

void Renderer::Render() {
    m_Shader->Bind();
    m_Shader->AddUniformMat4("cameraViewProjectionMatrix", m_Camera->GetViewProjectionMatrix());

    glBindVertexArray(s_Data.VaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.EboID);

    glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    m_Shader->Unbind();
}

void Renderer::OnDestroy() {
    if(s_Data.Vertices == nullptr) {
        Log::Warn("Vertices array was already nullptr, exiting Renderer::OnDestroy()");
        return;
    }

    glDeleteVertexArrays(1, &s_Data.VaoID);
    glDeleteBuffers(1, &s_Data.VboID);
    glDeleteBuffers(1, &s_Data.EboID);

    delete[] s_Data.Vertices;
    s_Data.Vertices = nullptr; // Keep track of if it is created or not
}

Quad* Renderer::AddQuad(const Quad& quad) {
    Quad* returnPnt = (Quad*) (s_Data.VertexPtr);

    (*s_Data.VertexPtr) = quad.V0;
    s_Data.VertexPtr++;

    (*s_Data.VertexPtr) = quad.V1;
    s_Data.VertexPtr++;

    (*s_Data.VertexPtr) = quad.V2;
    s_Data.VertexPtr++;

    (*s_Data.VertexPtr) = quad.V3;
    s_Data.VertexPtr++;

    s_Data.IndexCount += 6; 
    m_ShouldUpdateVertexData = true;

    return returnPnt;
}