#include "TestScene.h"

#include "HarmonyEngine.h"
#include <iostream>
#include <memory>
#include <array>

static Renderer s_Renderer = Renderer();
static GameObject s_GameObject = GameObject("Player");

void TestScene::OnCreate() {
    s_Renderer.OnCreate(&m_Camera);

    // Texture texture = Texture("assets/textures/image.png", 128, 128);
    // texture.Initialize();

    s_GameObject.AddComponent<QuadRenderer>();
}

void TestScene::Update(const float& deltaTime) {
    if(m_GameContext->GetInput().StandardInput.IsKey(GLFW_KEY_D)) {
        m_Camera.Move(glm::vec3(4 * deltaTime, 0, 0));
    }
    if(m_GameContext->GetInput().StandardInput.IsKey(GLFW_KEY_A)) {
        m_Camera.Move(glm::vec3(-4 * deltaTime, 0, 0));
    }
    if(m_GameContext->GetInput().StandardInput.IsKey(GLFW_KEY_W)) {
        m_Camera.Move(glm::vec3(0, 4 * deltaTime, 0));
    }
    if(m_GameContext->GetInput().StandardInput.IsKey(GLFW_KEY_S)) {
        m_Camera.Move(glm::vec3(0, -4 * deltaTime, 0));
    }

    s_Renderer.StartBatch();

    s_Renderer.EndBatch();
}

void TestScene::OnDestroy() {
    s_Renderer.OnDestroy();
}