#pragma once

// ======================================================================================
// Scene
// ======================================================================================

class Scene {

    friend class SceneManager;

protected:
    virtual void OnCreate();
    virtual void Update(const float& deltaTime);
    virtual void OnDestroy();
    
private:
    void HiddenOnCreate();
    void HiddenUpdate(const float& deltaTime);
    void HiddenOnDestroy();
    
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