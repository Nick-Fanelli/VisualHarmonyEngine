#include "Component.h"

#include "GameObject.h"

// ======================================================================================
// Component Class
// ======================================================================================
void Component::OnCreate() {}
void Component::Update(const float& deltaTime) {}
void Component::OnDestroy() {}

GameObject* Component::GetParentGameObject() { return m_ParentObject; }