#include "TestScene.h"

#include "HarmonyEngine.h"
#include <iostream>
#include <memory>

// Test Triangle Drawing Code
static std::vector<float> vertices = {
     -0.5f, 0.5f,    // Left top         ID: 0
     -0.5f, -0.5f,   // Left bottom      ID: 1
     0.5f, -0.5f,    // Right bottom     ID: 2
     0.5f, 0.5f      // Right left       ID: 3
};

static std::vector<uint32_t> indices = { 
    // Left bottom triangle
            0, 1, 2,
            // Right top triangle
            2, 3, 0
};

GLuint m_VaoID;
GLuint m_EboID;
std::unique_ptr<Shader> m_Shader;

void TestScene::OnCreate() {
    m_Shader = std::make_unique<Shader>("assets/shaders/default.vert.glsl", "assets/shaders/default.frag.glsl");

    // Bind the VAO
    glGenVertexArrays(1, &m_VaoID);
    glBindVertexArray(m_VaoID);

    // Bind the Verticies
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind Vertex Buffer

    // Push the data
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, (void*) 0); 

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind Buffer

    // Bind the indices
    glGenBuffers(1, &m_EboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboID); // Bind Indicies Buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind Buffer
    glBindVertexArray(0);

}

void TestScene::Update(const float& deltaTime) {
    m_Shader->Bind();

    glBindVertexArray(m_VaoID);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboID);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    m_Shader->Unbind();
}

void TestScene::OnDestroy() {
    
}