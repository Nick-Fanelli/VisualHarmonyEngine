#include "TestScene.h"

#include "HarmonyEngine.h"

static float s_CameraAspectRatio = 16.0f / 9.0f;
static float s_CameraZoomLevel = 1.0f;

void TestScene::OnCreate(GameContext* gameContextPtr) {
    m_GameContext = gameContextPtr;

    m_GameContext->GetRenderer().OnCreate(&m_Camera);

    auto texture = Texture("assets/textures/image.png");
    texture.Initialize();

    auto& textureID = m_GameContext->GetRenderer().AddTexture(texture);

    SpriteSheet spriteSheet = SpriteSheet(texture, texture.GetWidth() / 2, texture.GetHeight() / 2);

    Quad quad = Quad({0.0f, 0.0f}, {0.2f, 0.2f}, {1, 1, 1, 1}, textureID);
    spriteSheet.AssignToSprite(&quad, 0, 1);

    GameObject object = GameObject("Sample Object");
    AddGameObject(&object);
    object.AddComponent<Transform>();
    object.AddComponent<QuadRenderer>(quad);

//    for(float y = -10.0f; y < 10.0f; y += 0.25f) {
//        for(float x = -10.0f; x < 10.0f; x += 0.25f) {
//            GameObject object = GameObject("Generated Quad");
//            AddGameObject(&object);
//
//            glm::vec4 color = { (x + 10) / 20.0f, 0.2f, (y + 10) / 20.0f, 1.0f};
//            object.AddComponent<Transform>(glm::vec2(x, y));
//            object.AddComponent<QuadRenderer>(Quad({0.0f, 0.0f}, {0.2f, 0.2f}, color));
//        }
//    }
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

    s_CameraZoomLevel -= m_GameContext->GetInput().StandardInput.GetScrollPosition().y * 0.25f;
    s_CameraZoomLevel = std::max(s_CameraZoomLevel, 0.25f);
    m_Camera.SetProjection(-s_CameraAspectRatio * s_CameraZoomLevel, s_CameraAspectRatio * s_CameraZoomLevel, -s_CameraZoomLevel, s_CameraZoomLevel);

    RendererStatistics::Start();
    m_GameContext->GetRenderer().StartBatch();

    auto quadRendererGroup = m_Registry.group<QuadRenderer>(entt::get<Transform>);
    for(auto entity : quadRendererGroup) {
        auto[renderer, transform] = quadRendererGroup.get<QuadRenderer, Transform>(entity);
        m_GameContext->GetRenderer().DrawQuad(transform.Position, renderer.quad);
    }

    m_GameContext->GetRenderer().EndBatch();
    RendererStatistics::Stop();
}

void TestScene::OnDestroy() {
    m_Registry.clear<>();
    m_GameContext->GetRenderer().OnDestroy();
}

