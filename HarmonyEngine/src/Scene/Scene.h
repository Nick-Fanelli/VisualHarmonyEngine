#pragma once

// ======================================================================================
// Scene
// ======================================================================================

class Scene {

    friend class SceneManager;

    virtual void OnCreate();
    virtual void Update(const float& deltaTime);
    virtual void OnDestroy();
    
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