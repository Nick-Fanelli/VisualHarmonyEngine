#include "GameContext.h"
#include "../Scene/Scene.h"

namespace HarmonyEngine {

    void GameContext::Start(Scene* scene) {
        m_Display.CreateDisplay(this);

        m_SceneManager.SetActiveScene(scene);

        m_Display.StartGameLoop();
    }

    void GameContext::Update(const float& deltaTime) {
        m_SceneManager.Update(deltaTime);
    }

    void GameContext::Stop() {
        m_SceneManager.OnDestroy();
    }
}