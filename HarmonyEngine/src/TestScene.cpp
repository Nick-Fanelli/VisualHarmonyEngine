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

static GameObject gameObject = GameObject("Example Object");
static Mesh2D mesh = Mesh2D(&vertices, &indices);
static Sprite sprite = Sprite(&mesh, nullptr);
static SpriteRenderer spriteRenderer = SpriteRenderer(&sprite);

void TestScene::OnCreate() {
    mesh.Initialize();
    spriteRenderer.Initialize();

    spriteRenderer.SetColor(glm::vec4(0.001, 0.5, 1, 1));

    gameObject.AddComponent(&spriteRenderer);
    Scene::AddGameObject(&gameObject);
}

void TestScene::Update(const float& deltaTime) {
    
}

void TestScene::OnDestroy() {
    
}