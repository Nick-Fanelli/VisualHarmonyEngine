#pragma once

#include <string>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "../Core/Log.h"
#include "Component.h"

class Scene;

class GameObject {

    friend class Scene;

    Scene* m_ParentScene;

    std::string m_Name;
    std::vector<Component> m_Components;

    glm::vec2 m_Position;

    virtual void OnCreate() {}
    virtual void Update(const float& deltaTime) {}
    virtual void OnDestroy() {}

    void HiddenOnCreate();
    void HiddenUpdate(const float& deltaTime);
    void HiddenOnDestroy();

public:
    GameObject(std::string name) : m_Name(name), m_Position(glm::vec2()) {}

    virtual ~GameObject() { HiddenOnDestroy(); }

    const Scene* GetParentScene() const { return m_ParentScene; }

    const std::string& GetName() const { return m_Name; }
    const glm::vec2& GetPosition() const { return m_Position; }
    
    const void SetPosition(const glm::vec2& position) { m_Position = position; }

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        m_Components.push_back(T(std::forward<Args>(args)...));
        T& component = *static_cast<T*>(&m_Components.at(m_Components.size() - 1));
        component.SetParentObject(this);
        return component;
    }
};