#include "RenderComponents.h"

// ======================================================================================
// Mesh Renderer Component
// ======================================================================================
std::shared_ptr<Shader> MeshRenderer::s_DefaultShader = nullptr;

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh2D> mesh) : m_Mesh(mesh) {
    if(s_DefaultShader == nullptr) {
        s_DefaultShader = std::make_shared<Shader>("assets/shaders/mesh.vert.glsl", "assets/shaders/mesh.frag.glsl");
    }

    m_Shader = s_DefaultShader;
    m_Color = glm::vec4(1, 1, 1, 1);
}

void MeshRenderer::OnCreate() {

}

void MeshRenderer::Update(const float& deltaTime) {
    m_Shader->Bind();
    m_Shader->AddUniformVec4("color", m_Color);
    m_Shader->AddUniformVec3("cameraOffset", glm::vec3(0, 0, 0));

    glBindVertexArray(GetMesh()->GetVaoID());
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GetMesh()->GetEboID());

    glDrawElements(GL_TRIANGLES, GetMesh()->GetIndicesCount(), GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    m_Shader->Unbind();
}

void MeshRenderer::OnDestroy() {
    m_Shader->Dispose();
}

// ======================================================================================
// Sprite Renderer Component
// ======================================================================================

std::shared_ptr<Shader> SpriteRenderer::s_DefaultShader = nullptr;

SpriteRenderer::SpriteRenderer(Sprite sprite) : m_Sprite(sprite) {

    if(s_DefaultShader == nullptr) {
        s_DefaultShader = std::make_shared<Shader>("assets/shaders/default.vert.glsl", "assets/shaders/default.frag.glsl");
    }

    m_Shader = s_DefaultShader;
}

void SpriteRenderer::OnCreate() {

}

void SpriteRenderer::Update(const float& deltaTime) {
    m_Shader->Bind();
    m_Shader->Unbind();
}

void SpriteRenderer::OnDestroy() {
    m_Shader->Dispose();
}