#pragma once

#include <vector>
#include <memory>
// #include "GameObject.h"
#include "../Core/Log.h"

class GameObject;
class GameContext;

// ======================================================================================
// Scene
// ======================================================================================

class Scene {

    friend class SceneManager;

    std::vector<GameObject*> m_GameObjects;

    void HiddenOnCreate(GameContext* gameContext);
    void HiddenUpdate(const float& deltaTime);
    void HiddenOnDestroy();

protected:
    GameContext* m_GameContext = nullptr;

    virtual void OnCreate();
    virtual void Update(const float& deltaTime);
    virtual void OnDestroy();

public:
    Scene() : m_GameObjects(std::vector<GameObject*>()) {}

    ~Scene() { HiddenOnDestroy(); }

    void AddGameObject(GameObject* ptr);

    const GameContext* GetGameContext() const { return m_GameContext; }
};

// ======================================================================================
// Scene Manager
// ======================================================================================

class SceneManager {

    static GameContext* s_GameContext;
    static Scene* s_ActiveScene;

public:

    SceneManager(GameContext* gameContext);

    void Update(const float& deltaTime);
    void OnDestroy();

    static void SetActiveScene(Scene* m_ActiveScene);
    static const Scene* GetActiveScene() { return s_ActiveScene; }

};