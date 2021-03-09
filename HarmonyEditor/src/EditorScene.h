//
// Created by Nick Fanelli on 3/1/21.
//

#pragma once

#include "HarmonyEngine.h"

using namespace HarmonyEngine;

class EditorScene : public Scene {

    void OnCreate(GameContext* gameContext) override;
    void Update(const float& deltaTime) override;
    void OnDestroy() override;

};

