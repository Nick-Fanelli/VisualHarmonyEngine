//
// Created by Nick Fanelli on 3/16/21.
//

#pragma once

#include <harmonypch.h>

#include <Scene/Scene.h>

namespace HarmonyEditor {

    using namespace HarmonyEngine;

    struct RenderLayer {

        static Scene* s_Scene;

        static void Initialize(Scene* scene);
        static void RenderScene();
        static void CleanUp();

    };

}