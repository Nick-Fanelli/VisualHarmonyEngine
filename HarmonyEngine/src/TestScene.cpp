#include "TestScene.h"

#include "HarmonyEngine.h"
#include <iostream>
#include <memory>
#include <array>

static Renderer s_Renderer = Renderer();
static Quad* quadPtr;
static Quad* quad2Ptr;

void TestScene::OnCreate() {
    s_Renderer.OnCreate(&m_Camera);

    Texture texture = Texture("assets/textures/image.png", 128, 128);
    texture.Initialize();

    Texture texture2 = Texture("assets/textures/image2.png", 128, 128);
    texture2.Initialize();

    const int& texturePtr = s_Renderer.AddTexture(texture);
    const int& texture2Ptr = s_Renderer.AddTexture(texture2);

    Quad quad = Quad(glm::vec2(0.5, -0.5), { 1, 1}, { 1, 1, 1, 1 }, texturePtr);
    Quad quad2 = Quad(glm::vec2(-1.5, -0.5), { 1, 1 }, { 1, 1, 1, 1 }, texture2Ptr);

    quadPtr = s_Renderer.AddQuad(quad);
    quad2Ptr = s_Renderer.AddQuad(quad2);
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

    s_Renderer.Update(deltaTime);
}

void TestScene::OnDestroy() {
    s_Renderer.OnDestroy();
}