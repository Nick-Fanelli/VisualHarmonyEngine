#include "GameContext.h"
#include "Display.h"
#include "../Scene/Scene.h"

void GameContext::Start(Scene* scene) {
    m_Display = new Display();
    m_Display->CreateDisplay(this);

    m_SceneManager = new SceneManager(this);
    m_SceneManager->SetActiveScene(scene);

    m_Display->StartGameLoop();
}

void GameContext::Update(const float& deltaTime) {
    m_SceneManager->Update(deltaTime);
}

void GameContext::Stop() {
    m_SceneManager->OnDestroy();

    delete m_Display;
    delete m_SceneManager;
}