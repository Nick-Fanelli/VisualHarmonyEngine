//
// Created by Nick Fanelli on 3/14/21.
//

#pragma once

#include "harmonypch.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Core/GameContext.h>
#include <Scene/Scene.h>

using namespace HarmonyEngine;

struct RenderLayer {

    static Scene* s_Scene;

    static void Initialize(Scene* scene);
    static void RenderScene();
    static void CleanUp();

};

struct ImGuiLayer {

    static void Initialize(GameContext* gameContextPtr);
    static void RenderImGuiWindows();
    static void CleanUp();

};