#pragma once

#include <vector>
// #include "GameObject.h"

class GameObject;

// ======================================================================================
// Scene
// ======================================================================================

class Scene {

    friend class SceneManager;

    std::vector<GameObject*> m_GameObjects;

    void HiddenOnCreate();
    void HiddenUpdate(const float& deltaTime);
    void HiddenOnDestroy();

protected:
    virtual void OnCreate();
    virtual void Update(const float& deltaTime);
    virtual void OnDestroy();

public:
    Scene();

    void AddGameObject(GameObject* gameObject);
};

// ======================================================================================
// Scene Manager
// ======================================================================================

class SceneManager {

    static Scene* m_ActiveScene;

public:

    void Update(const float& deltaTime);
    void OnDestroy();

    static void SetActiveScene(Scene* m_ActiveScene);
    static const Scene* GetActiveScene() { return m_ActiveScene; }

};