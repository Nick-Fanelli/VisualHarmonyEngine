#pragma once

#include <string>
#include "../Core/Log.h"

class Scene;

class GameObject {

    friend class Scene;

    Scene* m_ParentScene;
    std::string m_Name;

    virtual void OnCreate();
    virtual void Update(const float& deltaTime);
    virtual void OnDestroy();

    void HiddenOnCreate();
    void HiddenUpdate(const float& deltaTime);
    void HiddenOnDestroy();

public:
    GameObject(std::string name) : m_Name(name) {}

    ~GameObject() {
        Log::Info("Deleting Game Object");
    }

    const Scene* GetParentScene() const { return m_ParentScene; }
    
    const std::string& GetName() const { return m_Name; }
};