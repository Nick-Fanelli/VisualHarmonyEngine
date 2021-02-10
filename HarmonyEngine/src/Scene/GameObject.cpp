#include "GameObject.h"
#include "Scene.h"

// Hidden Denfinitions
void GameObject::HiddenOnCreate() {
    OnCreate();
}

void GameObject::HiddenUpdate(const float& deltaTime) {
    for(Component& component : m_Components) component.Update(deltaTime);

    Update(deltaTime);
} 

void GameObject::HiddenOnDestroy() {
    m_ParentScene = nullptr;

    for(Component& component : m_Components) {
        component.OnDestroy();
    }

    m_Components.clear();

    OnDestroy();
}