//
// Created by Nick Fanelli on 3/16/21.
//

#pragma once

#include <harmonypch.h>
#include <imguipch.h>

#include <Core/GameContext.h>

namespace HarmonyEditor {

    using namespace HarmonyEngine;

    struct ImGuiLayer {

        static float s_Time;

        static void Initialize(GameContext* gameContextPtr);
        static void RenderImGuiWindows();
        static void CleanUp();

    };

}