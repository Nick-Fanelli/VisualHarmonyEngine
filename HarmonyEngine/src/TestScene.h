#pragma once

#include "HarmonyEngine.h"

class TestScene : public Scene {

    void OnCreate(GameContext* gameContextPtr) override;
    void Update(const float& deltaTime) override;
    void OnDestroy() override;

};