#include "Scene.h"

// ======================================================================================
// Scene 
// ======================================================================================

void Scene::OnCreate() {

}

void Scene::Update(const float& deltaTime) {

}

void Scene::OnDestroy() {

}

// ======================================================================================
// Scene Manager
// ======================================================================================

Scene* SceneManager::m_ActiveScene = nullptr;

void SceneManager::Update(const float& deltaTime) {
    if(m_ActiveScene != nullptr) m_ActiveScene->Update(deltaTime);
}

void SceneManager::OnDestroy() {
    if(m_ActiveScene != nullptr) m_ActiveScene->OnDestroy();
}

void SceneManager::SetActiveScene(Scene* scene) {
    if(m_ActiveScene != nullptr) m_ActiveScene->OnDestroy();

    scene->OnCreate();
    m_ActiveScene = scene;
}