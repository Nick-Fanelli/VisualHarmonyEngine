#include "Scene.h"

#include "../Core/Log.h"
#include "GameObject.h"
#include "../Core/GameContext.h"

// ======================================================================================
// Scene 
// ======================================================================================

Scene::Scene() : m_GameObjects(std::vector<GameObject*>()), m_Camera(OrthographicCamera(-CameraAspectRatio * CameraZoomLevel, CameraAspectRatio * CameraZoomLevel, -CameraZoomLevel, CameraZoomLevel)) {
}

// Definition for Override Methods
void Scene::OnCreate() {
    // m_Renderer.OnCreate(&m_Camera);
}

void Scene::Update(const float& deltaTime) {}
void Scene::OnDestroy() {}

void Scene::HiddenOnCreate(GameContext* gameContext) {
    m_GameContext = gameContext;
    OnCreate();
}

void Scene::HiddenUpdate(const float& deltaTime) {
    for(auto& gameObject : m_GameObjects) {
        gameObject->HiddenUpdate(deltaTime);
    }

    Update(deltaTime);
}

void Scene::HiddenOnDestroy() {
    for(auto& gameObject : m_GameObjects) {
        gameObject->OnDestroy();
    }

    m_GameObjects.clear();
    m_GameContext = nullptr;

    OnDestroy();
}

void Scene::AddGameObject(GameObject* gameObjectPtr) {
    gameObjectPtr->m_ParentScene = this;
    gameObjectPtr->HiddenOnCreate();
    m_GameObjects.push_back(gameObjectPtr);
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
        s_ActiveScene->HiddenUpdate(deltaTime);
    }
}

void SceneManager::OnDestroy() {
    s_GameContext = nullptr;
    if(s_ActiveScene != nullptr) s_ActiveScene->HiddenOnDestroy();
}

void SceneManager::SetActiveScene(Scene* scene) {
    if(s_ActiveScene != nullptr) s_ActiveScene->HiddenOnDestroy();

    scene->HiddenOnCreate(SceneManager::s_GameContext);
    s_ActiveScene = scene;
}