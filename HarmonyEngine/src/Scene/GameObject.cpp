#include "GameObject.h"
#include "Scene.h"
#include "Component.h"

// Virtual Override Definitions
void GameObject::OnCreate() {}
void GameObject::Update(const float& deltaTime) {}
void GameObject::OnDestroy() {}

// Hidden Denfinitions

void GameObject::HiddenOnCreate() {
    OnCreate();
}

void GameObject::HiddenUpdate(const float& deltaTime) {
    for(auto& component : m_Components) component->Update(deltaTime);

    Update(deltaTime);
} 

void GameObject::HiddenOnDestroy() {
    m_ParentScene = nullptr;

    for(auto& component : m_Components) {
        component->OnDestroy();
    }

    m_Components.clear();

    OnDestroy();
}

// Public Methods

void GameObject::AddComponent(std::shared_ptr<Component> component) {
    component->SetParentObject(this);
    component->OnCreate();
    
    m_Components.push_back(component);
}