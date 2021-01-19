#pragma once

// #include "HarmonyEngine.h"
#include "Scene/Scene.h"
#include "Core/Log.h"

class TestScene : public Scene {

    void OnCreate() override;
    void Update(const float& deltaTime) override;
    void OnDestroy() override;

};