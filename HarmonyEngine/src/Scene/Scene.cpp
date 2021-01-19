#include "Scene.h"

#include "../Core/Log.h"
#include "GameObject.h"

// ======================================================================================
// Scene 
// ======================================================================================

// Definition for Override Methods
void Scene::OnCreate() {}
void Scene::Update(const float& deltaTime) {}
void Scene::OnDestroy() {}

Scene::Scene() : m_GameObjects(std::vector<std::shared_ptr<GameObject>>()) {}

void Scene::HiddenOnCreate() {
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
    OnDestroy();
}

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObjectPtr) {
    gameObjectPtr->m_ParentScene = this;
    gameObjectPtr->HiddenOnCreate();
    m_GameObjects.push_back(gameObjectPtr);
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