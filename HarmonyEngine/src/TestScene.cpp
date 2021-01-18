#include "TestScene.h"

#include "HarmonyEngine.h"

// Shader shader;
// Mesh2D mesh;

static Mesh2D* mesh;
static Shader* shader;

// Test Triangle Drawing Code
static std::vector<float> vertices = {
     -0.5f, 0.5f,    // Left top         ID: 0
     -0.5f, -0.5f,   // Left bottom      ID: 1
     0.5f, -0.5f,    // Right bottom     ID: 2
     0.5f, 0.5f      // Right left       ID: 3
};

static std::vector<unsigned int> indices = { 
    // Left bottom triangle
            0, 1, 2,
            // Right top triangle
            2, 3, 0
};

static std::vector<float> colors = {
    1, 0, 0, 1,  // Red color, for the first vertex
    0, 1, 0, 1,  // Green color, for the second vertex
    0, 0, 1, 1   // Blue color, for the third vertex
};

void TestScene::OnCreate() {
    mesh = new Mesh2D(vertices, indices);
    shader = new Shader("HarmonyEngine/assets/shaders/mesh.vert.glsl", "HarmonyEngine/assets/shaders/mesh.frag.glsl");
}

void TestScene::Update(const float& deltaTime) {
    shader->Bind();

    glBindVertexArray(mesh->GetVaoID());
    glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetEboID());

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    shader->Unbind();
}

void TestScene::OnDestroy() {
    shader->Dispose();

    delete shader;
    delete mesh;
}