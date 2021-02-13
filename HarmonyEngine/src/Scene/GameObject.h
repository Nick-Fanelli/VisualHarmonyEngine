#pragma once

#include <string>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "../Core/Log.h"
#include "Component.h"

#include <entt.hpp>

class Scene;

class GameObject {

    Scene* m_ParentScene;

    std::string m_Name;

    glm::vec2 m_Position;

public:
    GameObject(std::string name) : m_Name(name), m_Position(glm::vec2()) {}

    virtual ~GameObject() { OnDestroy(); }

    virtual void OnCreate();
    virtual void Update(const float& deltaTime);
    virtual void OnDestroy();

    const Scene* GetParentScene() const { return m_ParentScene; }

    const std::string& GetName() const { return m_Name; }
    const glm::vec2& GetPosition() const { return m_Position; }
    
    const void SetPosition(const glm::vec2& position) { m_Position = position; }

    void SetParentScene(Scene* scene) { m_ParentScene = scene; }

    template <typename T, typename... Args>
    void AddComponent(Args&&... args) {
    }
};