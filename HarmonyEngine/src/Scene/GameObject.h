#pragma once

class Scene;

class GameObject {

    friend class Scene;

    Scene* m_ParentScene;

    virtual void OnCreate();
    virtual void Update(const float& deltaTime);
    virtual void OnDestroy();

    void HiddenOnCreate();
    void HiddenUpdate(const float& deltaTime);
    void HiddenOnDestroy();

public:
    const Scene* GetParentScene() const { return m_ParentScene; }
};