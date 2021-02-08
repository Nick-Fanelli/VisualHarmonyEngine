#include "TestScene.h"

#include "HarmonyEngine.h"
#include <iostream>
#include <memory>
#include <array>

static Renderer s_Renderer = Renderer();
// static Quad s_Quad = Quad({0, 0}, {1, 1}, {1, 1, 1, 1});
static int s_TextureID;

void TestScene::OnCreate() {
    s_Renderer.OnCreate(&m_Camera);

    Texture texture = Texture("assets/textures/image.png", 128, 128);
    texture.Initialize();

    Texture texture2 = Texture("assets/textures/image2.png", 128, 128);
    texture2.Initialize();

    s_TextureID = s_Renderer.AddTexture(texture);
    s_Renderer.AddTexture(texture2);
}

void TestScene::Update(const float& deltaTime) {
    s_Renderer.StartBatch();

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

    s_Renderer.DrawQuad({0, 0}, {1, 1}, { 0, 1, 1, 1 }, s_TextureID);

    s_Renderer.EndBatch();
}

void TestScene::OnDestroy() {
    s_Renderer.OnDestroy();
}