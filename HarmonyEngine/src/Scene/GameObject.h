#pragma once

#include <string>
#include <memory>
#include <vector>
#include "../Core/Log.h"

class Scene;
class Component;

class GameObject {

    friend class Scene;

    Scene* m_ParentScene;
    std::string m_Name;

    std::vector<std::shared_ptr<Component>> m_Components;

    virtual void OnCreate();
    virtual void Update(const float& deltaTime);
    virtual void OnDestroy();

    void HiddenOnCreate();
    void HiddenUpdate(const float& deltaTime);
    void HiddenOnDestroy();

public:
    GameObject(std::string name) : m_Name(name) {}

    virtual ~GameObject() { HiddenOnDestroy(); }

    void AddComponent(std::shared_ptr<Component> component);

    const Scene* GetParentScene() const { return m_ParentScene; }
    const std::string& GetName() const { return m_Name; }
};