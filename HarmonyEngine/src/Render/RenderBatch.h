#pragma once

#include <array>
#include <vector>
#include <memory>
#include "RenderComponents.h"
#include <iostream>

// ======================================================================================
// Render Batch
// ======================================================================================

static const size_t MAX_QUAD_COUNT = 1000;
static const size_t MAX_VERTEX_COUNT = MAX_QUAD_COUNT * 4;
static const size_t MAX_INDEX_COUNT = MAX_QUAD_COUNT * 6;

class RenderBatch {

    size_t m_Size;

    std::array<SpriteRenderer*, MAX_QUAD_COUNT> m_SpriteRenderers;
    std::array<Vertex, MAX_VERTEX_COUNT> m_Vertices;

    GLuint m_VaoID;
    GLuint m_VboID;

    std::shared_ptr<Shader> m_Shader;

public:
    RenderBatch() {}

    void OnCreate() {
        m_Shader = std::make_shared<Shader>("assets/shaders/default.vert.glsl", "assets/shaders/default.frag.glsl");

        // Generate and bind a new VAO
        glGenVertexArrays(1, &m_VaoID);
        glBindVertexArray(m_VaoID);

        // Allocate space for vertices
        glGenBuffers(1, &m_VboID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
        glBufferData(GL_ARRAY_BUFFER, MAX_VERTEX_COUNT * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

        // Enable and add Buffer Attribute Pointers
        // Store Position Data at Attrib 0
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, Position));

        // Store Color Data at Attrib 1
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, Color));

        // Create the indices
        uint32_t indices[MAX_INDEX_COUNT];
        uint32_t offset = 0;
        for(size_t i = 0; i < MAX_INDEX_COUNT; i += 6) {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;

            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;

            offset += 4;
        }

        // Generate and bind the indices
        GLuint iboID;
        glGenBuffers(1, &iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



    }

    void AddRenderComponent(SpriteRenderer* spriteRenderer) {
        uint32_t index = m_Size;
        m_SpriteRenderers[index] = spriteRenderer;
        m_Size++;

        LoadVertexProperties(spriteRenderer, index);
    }

    void Render() {
        glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(Vertex), m_Vertices.data());

        m_Shader->Bind();

        glBindVertexArray(m_VaoID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);

        m_Shader->Unbind();
    }

    void LoadVertexProperties(SpriteRenderer* renderer, uint32_t& index) {
        m_Vertices[index] = renderer->GetSprite()->m_Mesh->GetVertices()->at(0);
        m_Vertices[index + 1] = renderer->GetSprite()->m_Mesh->GetVertices()->at(1);
        m_Vertices[index + 2] = renderer->GetSprite()->m_Mesh->GetVertices()->at(2);
        m_Vertices[index + 3] = renderer->GetSprite()->m_Mesh->GetVertices()->at(3);
    }

};