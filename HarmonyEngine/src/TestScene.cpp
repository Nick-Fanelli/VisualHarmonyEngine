#include "TestScene.h"

#include "HarmonyEngine.h"
#include <iostream>
#include <memory>

void TestScene::OnCreate() {
    m_Renderer = Renderer(this);
    m_Renderer.OnCreate();
}

void TestScene::Update(const float& deltaTime) {
    m_Renderer.Update(deltaTime);
}

void TestScene::OnDestroy() {
    m_Renderer.OnDestroy();
}