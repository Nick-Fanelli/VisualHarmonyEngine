#include "TestScene.h"

#include "HarmonyEngine.h"
#include <iostream>
#include <memory>

// Test Triangle Drawing Code
static std::vector<float> vertices = {
     -0.5f, 0.5f,    // Left top         ID: 0
     -0.5f, -0.5f,   // Left bottom      ID: 1
     0.5f, -0.5f,    // Right bottom     ID: 2
     0.5f, 0.5f      // Right left       ID: 3
};

static std::vector<uint32_t> indices = { 
    // Left bottom triangle
            0, 1, 2,
            // Right top triangle
            2, 3, 0
};

static float cameraAspectRatio = 1280.0f / 720.0f;
static float cameraZoomLevel = 1.0f;
static OrthographicCamera camera = OrthographicCamera(-cameraAspectRatio * cameraZoomLevel, cameraAspectRatio * cameraZoomLevel, -cameraZoomLevel, cameraZoomLevel);

static GameObject gameObject = GameObject("Example Object");
static Mesh2D mesh = Mesh2D(&vertices, &indices);
static Sprite sprite = Sprite(&mesh, nullptr);
static SpriteRenderer spriteRenderer = SpriteRenderer(&sprite);

void TestScene::OnCreate() {

    mesh.Initialize();
    spriteRenderer.Initialize(&camera);

    spriteRenderer.SetColor(glm::vec4(0.001, 0.5, 1, 1));

    gameObject.AddComponent(&spriteRenderer);
    Scene::AddGameObject(&gameObject);
}

void TestScene::Update(const float& deltaTime) {
    if(m_GameContext->GetInput().StandardInput.IsKey(GLFW_KEY_LEFT)) {
        glm::vec3 cameraPos = camera.GetPosition();

        cameraPos.x -= cos(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;
        cameraPos.y -= sin(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;

        camera.SetPosition(cameraPos);
    }

    if(m_GameContext->GetInput().StandardInput.IsKey(GLFW_KEY_RIGHT)) {
        glm::vec3 cameraPos = camera.GetPosition();

        cameraPos.x += cos(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;
        cameraPos.y += sin(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;

        camera.SetPosition(cameraPos);
    }

    if(m_GameContext->GetInput().StandardInput.IsKey(GLFW_KEY_UP)) {
        glm::vec3 cameraPos = camera.GetPosition();

        cameraPos.x += -sin(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;
        cameraPos.y += cos(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;

        camera.SetPosition(cameraPos);
    }

    if(m_GameContext->GetInput().StandardInput.IsKey(GLFW_KEY_DOWN)) {
        glm::vec3 cameraPos = camera.GetPosition();

        cameraPos.x -= -sin(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;
        cameraPos.y -= cos(glm::radians(camera.GetRotation())) * 5.0f * deltaTime;

        camera.SetPosition(cameraPos);
    }

    cameraZoomLevel -= m_GameContext->GetInput().StandardInput.GetScrollPosition().y * 0.25f;
    cameraZoomLevel = std::max(cameraZoomLevel, 0.25f);
    camera.SetProjection(-cameraAspectRatio * cameraZoomLevel, cameraAspectRatio * cameraZoomLevel, -cameraZoomLevel, cameraZoomLevel);
}

void TestScene::OnDestroy() {
    
}