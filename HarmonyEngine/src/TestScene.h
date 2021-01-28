#pragma once

#include "HarmonyEngine.h"

class TestScene : public Scene {

    Renderer m_Renderer;

    void OnCreate() override;
    void Update(const float& deltaTime) override;
    void OnDestroy() override;

public:
    TestScene() : m_Renderer(Renderer(this)) {}

};