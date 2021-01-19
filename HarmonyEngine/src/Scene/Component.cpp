#include "Component.h"
#include "GameObject.h"

// ======================================================================================
// Component Class
// ======================================================================================
void Component::OnCreate() {}
void Component::Update(const float& deltaTime) {}
void Component::OnDestroy() {}

// ======================================================================================
// Mesh Renderer Component
// ======================================================================================
void MeshRenderer::OnCreate() {

}

void MeshRenderer::Update(const float& deltaTime) {

    // glBindVertexArray(GetMesh()->GetVaoID());
    // glEnableVertexAttribArray(0);
    // // glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GetMesh()->GetEboID());

    // glDrawElements(GL_TRIANGLES, GetMesh()->GetIndicesCount(), GL_UNSIGNED_INT, 0);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // glDisableVertexAttribArray(0);
    // // glDisableVertexAttribArray(1);
    // glBindVertexArray(0);

}

void MeshRenderer::OnDestroy() {
}