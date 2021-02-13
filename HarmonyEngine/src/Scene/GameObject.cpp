#include "GameObject.h"
#include "Scene.h"

void GameObject::OnCreate() {

}

void GameObject::Update(const float& deltaTime) {
    for(auto& component : m_Components) {
        component.Update(deltaTime);
    }
}

void GameObject::OnDestroy() {
    for(auto& component : m_Components) {
        component.OnDestroy();
    }
}