#include "TestScene.h"

#include "HarmonyEngine.h"

static GameObject s_GameObject = GameObject("Player");

void TestScene::OnCreate(GameContext* gameContextPtr) {
    m_GameContext = gameContextPtr;

    Renderer::OnCreate(&m_Camera);

    Texture texture = Texture("assets/textures/image.png", 128, 128);
    texture.Initialize();

    const int& textureID = Renderer::AddTexture(texture);

    AddGameObject(&s_GameObject);

    s_GameObject.AddComponent<Transform>(glm::vec2(-0.5f, -0.5f));
    s_GameObject.AddComponent<QuadRenderer>(Quad({-0.5f, -0.5f}, {1, 1}, {1, 1, 1, 1}, textureID));
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

    Renderer::StartBatch();

    auto quadRendererGroup = m_Registry.group<QuadRenderer>(entt::get<Transform>);
    for(auto entity : quadRendererGroup) {
        auto[renderer, transform] = quadRendererGroup.get<QuadRenderer, Transform>(entity);
        Renderer::DrawQuad(transform.Position, renderer.quad);
    }

    Renderer::EndBatch();
}

void TestScene::OnDestroy() {
    m_Registry.clear<>();
}

