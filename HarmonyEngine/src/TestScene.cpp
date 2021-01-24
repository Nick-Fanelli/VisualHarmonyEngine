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

static std::vector<unsigned int> indices = { 
    // Left bottom triangle
            0, 1, 2,
            // Right top triangle
            2, 3, 0
};

void TestScene::OnCreate() {
    std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>("Example Object");

    std::shared_ptr<Mesh2D> mesh = std::make_shared<Mesh2D>(vertices, indices);

    Sprite sprite = Sprite(mesh, nullptr);

    std::shared_ptr<SpriteRenderer> spriteRenderer = std::make_shared<SpriteRenderer>(sprite);
    gameObject->AddComponent(spriteRenderer);

    Scene::AddGameObject(gameObject);
}

void TestScene::Update(const float& deltaTime) {
    
}

void TestScene::OnDestroy() {
    
}