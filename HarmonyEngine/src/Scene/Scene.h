#pragma once

#include "harmonypch.h"
#include "../Render/Renderer.h"
#include "Camera.h"

namespace HarmonyEngine {

    class GameContext;

// ======================================================================================
// Scene
// ======================================================================================

    static const float CameraAspectRatio = 1280.0f / 720.0f;
    static const float CameraZoomLevel = 1.0f;

    class Scene {

        friend class SceneManager;

    protected:
        GameContext* m_GameContext = nullptr;
        OrthographicCamera m_Camera;

        virtual void OnCreate(GameContext* gameContext);
        virtual void Update(const float& deltaTime);
        virtual void OnDestroy();

    public:
        entt::registry m_Registry;

        Scene();

        entt::entity CreateGameObject();

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
}