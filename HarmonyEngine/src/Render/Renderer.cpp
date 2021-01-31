#include "Renderer.h"

#include <iostream>

#include "../Scene/Scene.h"
#include "../Core/Utils.h"

static const size_t MaxQuadCount = 1000;
static const size_t MaxVertexCount = MaxQuadCount * 4;
static const size_t MaxIndexCount = MaxQuadCount * 6;

// static const size_t MaxTextureCount = OpenGLUtils::GetGPUMaxTextureSlots();

struct RenderBatch {

    GLuint VaoID = 0;
    GLuint VboID = 0;
    GLuint EboID = 0;

    uint32_t IndexCount = 0;
    uint32_t TextureCount = 0;

    Vertex* Vertices = nullptr;
    Vertex* VertexPtr = nullptr;
};

static RenderBatch s_Batch;

void Renderer::OnCreate(OrthographicCamera* camera) {
    if(s_Batch.Vertices != nullptr) {
        Log::Error("Vertices array was not nullptr, exiting Renderer::OnCreate()");
        return;
    }

    s_Batch = RenderBatch();
    s_Batch.Vertices = new Vertex[MaxVertexCount];
    s_Batch.VertexPtr = s_Batch.Vertices;

    m_Camera = camera;
    m_Shader = std::make_unique<Shader>("assets/shaders/default.vert.glsl", "assets/shaders/default.frag.glsl");

    // Bind the VAO
    glGenVertexArrays(1, &s_Batch.VaoID);
    glBindVertexArray(s_Batch.VaoID);

    // Bind the Verticies
    glGenBuffers(1, &s_Batch.VboID);
    glBindBuffer(GL_ARRAY_BUFFER, s_Batch.VboID); // Bind Vertex Buffer

    // Push the data
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MaxVertexCount, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, Position));
    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, Color));
    glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, TextureCoord));
    glVertexAttribPointer(3, 1, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, TextureID));

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
    glGenBuffers(1, &s_Batch.EboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Batch.EboID); // Bind Indicies Buffer
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

    GLsizeiptr size = (uint8_t*) s_Batch.VertexPtr - (uint8_t*) s_Batch.Vertices;

    glBindBuffer(GL_ARRAY_BUFFER, s_Batch.VboID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Batch.Vertices);
}

void Renderer::Render() {
    m_Shader->Bind();
    m_Shader->AddUniformMat4("cameraViewProjectionMatrix", m_Camera->GetViewProjectionMatrix());

    glBindVertexArray(s_Batch.VaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Batch.EboID);

    glDrawElements(GL_TRIANGLES, s_Batch.IndexCount, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glBindVertexArray(0);

    m_Shader->Unbind();
}

void Renderer::OnDestroy() {
    if(s_Batch.Vertices == nullptr) {
        Log::Warn("Vertices array was already nullptr, exiting Renderer::OnDestroy()");
        return;
    }

    glDeleteVertexArrays(1, &s_Batch.VaoID);
    glDeleteBuffers(1, &s_Batch.VboID);
    glDeleteBuffers(1, &s_Batch.EboID);

    delete[] s_Batch.Vertices;
    s_Batch.Vertices = nullptr; // Keep track of if it is created or not
}

Quad* Renderer::AddQuad(const Quad& quad) {
    Quad* returnPnt = (Quad*) (s_Batch.VertexPtr);

    (*s_Batch.VertexPtr) = quad.V0;
    s_Batch.VertexPtr++;

    (*s_Batch.VertexPtr) = quad.V1;
    s_Batch.VertexPtr++;

    (*s_Batch.VertexPtr) = quad.V2;
    s_Batch.VertexPtr++;

    (*s_Batch.VertexPtr) = quad.V3;
    s_Batch.VertexPtr++;

    s_Batch.IndexCount += 6; 
    m_ShouldUpdateVertexData = true;

    return returnPnt;
}