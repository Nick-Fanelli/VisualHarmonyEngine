#pragma once

#include <string>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "../Core/Log.h"

class Scene;
class Component;

class GameObject {

    friend class Scene;

    Scene* m_ParentScene;

    std::string m_Name;
    std::vector<Component*> m_Components;

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

    void AddComponent(Component* component);

    const Scene* GetParentScene() const { return m_ParentScene; }

    const std::string& GetName() const { return m_Name; }
    const glm::vec2& GetPosition() const { return m_Position; }
    
    const void SetPosition(const glm::vec2& position) { m_Position = position; }
};