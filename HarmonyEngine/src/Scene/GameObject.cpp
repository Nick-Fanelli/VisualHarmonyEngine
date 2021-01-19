#include "GameObject.h"
#include "Scene.h"

// Virtual Override Definitions
void GameObject::OnCreate() {}
void GameObject::Update(const float& deltaTime) {}
void GameObject::OnDestroy() {}

// Hidden Denfinitions

void GameObject::HiddenOnCreate() {
    OnCreate();
}

void GameObject::HiddenUpdate(const float& deltaTime) {
    Update(deltaTime);
} 

void GameObject::HiddenOnDestroy() {
    m_ParentScene = nullptr;
    OnDestroy();
}