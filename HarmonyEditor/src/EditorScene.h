//
// Created by Nick Fanelli on 3/1/21.
//

#pragma once

#include "harmonypch.h"
#include "HarmonyEngine.h"

namespace HarmonyEditor {

    using namespace HarmonyEngine;

    class EditorScene : public Scene {

        virtual void OnCreate(GameContext* gameContext) override;
        virtual void Update(const float& deltaTime) override;
        virtual void OnDestroy() override;

    };

}