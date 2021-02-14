#include "Scene.h"

#include "../Core/Log.h"
#include "GameObject.h"
#include "../Core/GameContext.h"

// ======================================================================================
// Scene 
// ======================================================================================

Scene::Scene() : m_Camera(OrthographicCamera(-CameraAspectRatio * CameraZoomLevel, CameraAspectRatio * CameraZoomLevel, -CameraZoomLevel, CameraZoomLevel)) {
}

// Definition for Override Methods
void Scene::OnCreate(GameContext* gameContext) {
    m_GameContext = gameContext;
}

void Scene::Update(const float& deltaTime) {}
void Scene::OnDestroy() {}

void Scene::AddGameObject(GameObject* gameObjectPtr) {
    entt::entity entityID = m_Registry.create();

    gameObjectPtr->SetParentScene(this);
    gameObjectPtr->OnCreate(entityID);
}

// ======================================================================================
// Scene Manager
// ======================================================================================

Scene* SceneManager::s_ActiveScene = nullptr;
GameContext* SceneManager::s_GameContext = nullptr;

SceneManager::SceneManager(GameContext* gameContext) {
    SceneManager::s_GameContext = gameContext;
}

void SceneManager::Update(const float& deltaTime) {
    if(s_ActiveScene != nullptr) {
        s_ActiveScene->Update(deltaTime);
    }
}

void SceneManager::OnDestroy() {
    s_GameContext = nullptr;
    if(s_ActiveScene != nullptr) s_ActiveScene->OnDestroy();
}

void SceneManager::SetActiveScene(Scene* scene) {
    if(s_ActiveScene != nullptr) s_ActiveScene->OnDestroy();

    scene->OnCreate(SceneManager::s_GameContext);
    s_ActiveScene = scene;
}