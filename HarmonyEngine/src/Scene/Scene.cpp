#include "Scene.h"

#include "../Core/Log.h"

// ======================================================================================
// Scene 
// ======================================================================================

// Definition for Override Methods
void Scene::OnCreate() {}
void Scene::Update(const float& deltaTime) {}
void Scene::OnDestroy() {}

void Scene::HiddenOnCreate() {
    OnCreate();
}

void Scene::HiddenUpdate(const float& deltaTime) {
    Update(deltaTime);
}

void Scene::HiddenOnDestroy() {
    OnDestroy();
}

// ======================================================================================
// Scene Manager
// ======================================================================================

Scene* SceneManager::m_ActiveScene = nullptr;

void SceneManager::Update(const float& deltaTime) {
    if(m_ActiveScene != nullptr) m_ActiveScene->HiddenUpdate(deltaTime);
}

void SceneManager::OnDestroy() {
    if(m_ActiveScene != nullptr) m_ActiveScene->HiddenOnDestroy();
}

void SceneManager::SetActiveScene(Scene* scene) {
    if(m_ActiveScene != nullptr) m_ActiveScene->HiddenOnDestroy();

    scene->HiddenOnCreate();
    m_ActiveScene = scene;
}