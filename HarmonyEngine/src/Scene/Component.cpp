#include "Component.h"

#include "GameObject.h"

// ======================================================================================
// Component Class
// ======================================================================================
void Component::OnCreate() {}
void Component::Update(const float& deltaTime) {}
void Component::OnDestroy() {}

GameObject* Component::GetParentGameObject() { return m_ParentObject; }

// ======================================================================================
// Quad Renderer Componet
// ======================================================================================
void QuadRenderer::OnCreate() {}

void QuadRenderer::Update(const float& deltaTime) {
    Log::Info("Hello World!");
    Renderer::DrawQuad(m_Quad);
}

void QuadRenderer::OnDestroy() {}