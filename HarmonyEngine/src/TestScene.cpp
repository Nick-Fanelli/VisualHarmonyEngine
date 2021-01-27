#include "TestScene.h"

#include "HarmonyEngine.h"
#include <iostream>
#include <memory>
#include <vector>

static std::vector<uint32_t> indices = { 
    0, 1, 2,
    2, 3, 0,
};

// static float cameraAspectRatio = 1280.0f / 720.0f;
// static float cameraZoomLevel = 1.0f;
// static OrthographicCamera camera = OrthographicCamera(-cameraAspectRatio * cameraZoomLevel, cameraAspectRatio * cameraZoomLevel, -cameraZoomLevel, cameraZoomLevel);

std::vector<Vertex> CreateQuad(float x, float y) {
    Vertex v0;
    v0.Position = glm::vec2(-0.5f + x, 0.5f + y);
    v0.Color = glm::vec4(1, 0, 0, 1);

    Vertex v1;
    v1.Position = glm::vec2(-0.5f + x, -0.5f + y);
    v1.Color = glm::vec4(0, 1, 0, 1);

    Vertex v2;
    v2.Position = glm::vec2(0.5f + x, -0.5f + y);
    v2.Color = glm::vec4(0, 0, 1, 1);

    Vertex v3;
    v3.Position = glm::vec2(0.5f + x, 0.5f + y);
    v3.Color = glm::vec4(1, 0, 1, 1);

    return { v0, v1, v2, v3 };
}

static RenderBatch batch;

static GameObject gameObject = GameObject("Example Object");
static std::vector<Vertex> vertices = CreateQuad(0, 0);
static Mesh2D mesh = Mesh2D(&vertices, &indices);
static Sprite sprite = Sprite(&mesh, nullptr);
static SpriteRenderer renderer = SpriteRenderer(&sprite);

void TestScene::OnCreate() {

    gameObject.AddComponent(&renderer);
    batch = RenderBatch();
    batch.OnCreate();
    batch.AddRenderComponent(&renderer);

    // Scene::AddGameObject(&gameObject);
}

void TestScene::Update(const float& deltaTime) {
    batch.Render();
    // if(m_GameContext->GetInput().StandardInput.IsKey(GLFW_KEY_A)) {
    //     glm::vec3 cameraPos = camera.GetPosition();

    //     cameraPos.x -= cos(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;
    //     cameraPos.y -= sin(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;

    //     camera.SetPosition(cameraPos);
    // }

    // if(m_GameContext->GetInput().StandardInput.IsKey(GLFW_KEY_D)) {
    //     glm::vec3 cameraPos = camera.GetPosition();

    //     cameraPos.x += cos(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;
    //     cameraPos.y += sin(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;

    //     camera.SetPosition(cameraPos);
    // }

    // if(m_GameContext->GetInput().StandardInput.IsKey(GLFW_KEY_W)) {
    //     glm::vec3 cameraPos = camera.GetPosition();

    //     cameraPos.x += -sin(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;
    //     cameraPos.y += cos(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;

    //     camera.SetPosition(cameraPos);
    // }

    // if(m_GameContext->GetInput().StandardInput.IsKey(GLFW_KEY_S)) {
    //     glm::vec3 cameraPos = camera.GetPosition();

    //     cameraPos.x -= -sin(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;
    //     cameraPos.y -= cos(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;

    //     camera.SetPosition(cameraPos);
    // }

    // cameraZoomLevel -= m_GameContext->GetInput().StandardInput.GetScrollPosition().y * 0.25f;
    // cameraZoomLevel = std::max(cameraZoomLevel, 0.25f);
    // camera.SetProjection(-cameraAspectRatio * cameraZoomLevel, cameraAspectRatio * cameraZoomLevel, -cameraZoomLevel, cameraZoomLevel);
}

void TestScene::OnDestroy() {
    
}