//
// Created by Nick Fanelli on 3/1/21.
//

#include "EditorScene.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace HarmonyEngine;

void EditorScene::OnCreate(GameContext* gameContext) {
    m_GameContext = gameContext;
    Renderer::OnCreate(&m_Camera);

    const char* glsl_version = "#version 150";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO();
//    (void) io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(gameContext->GetDisplay().GetWindowPointer(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void EditorScene::Update(const float& deltaTime) {
    // Start ImGui Frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Hello, World");
    ImGui::Text("This is some useful text");
    ImGui::End();

    // End ImGui Frame
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorScene::OnDestroy() {
    // Clean-up ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
