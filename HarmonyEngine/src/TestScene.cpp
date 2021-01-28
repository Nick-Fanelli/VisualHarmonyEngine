#include "TestScene.h"

#include "HarmonyEngine.h"
#include <iostream>
#include <memory>

static Renderer s_Renderer = Renderer();

void TestScene::OnCreate() {
    s_Renderer.OnCreate();
}

void TestScene::Update(const float& deltaTime) {
    s_Renderer.Update(deltaTime);
}

void TestScene::OnDestroy() {
    s_Renderer.OnDestroy();
}