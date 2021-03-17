//
// Created by Nick Fanelli on 3/16/21.
//

#pragma once

#include <harmonypch.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

#include <Core/GameContext.h>

using namespace HarmonyEngine;

struct ImGuiLayer {

    static float s_Time;

    static void Initialize(GameContext* gameContextPtr);
    static void RenderImGuiWindows();
    static void CleanUp();

};