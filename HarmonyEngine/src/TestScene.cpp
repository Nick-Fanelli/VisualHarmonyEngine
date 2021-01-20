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

static std::vector<float> colors = {
    1, 0, 0, 1,  // Red color, for the first vertex
    0, 1, 0, 1,  // Green color, for the second vertex
    0, 0, 1, 1   // Blue color, for the third vertex
};

void TestScene::OnCreate() {
    std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>("Example Object");

    std::shared_ptr<Mesh2D> mesh = std::make_shared<Mesh2D>(vertices, indices);
    std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>(mesh);

    gameObject->AddComponent(meshRenderer);
    Scene::AddGameObject(gameObject);
}

void TestScene::Update(const float& deltaTime) {
    
}

void TestScene::OnDestroy() {

}