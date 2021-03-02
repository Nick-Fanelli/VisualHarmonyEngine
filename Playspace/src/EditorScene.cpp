//
// Created by Nick Fanelli on 3/1/21.
//

#include "EditorScene.h"

#include "entt/entt.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace HarmonyEngine;

static Quad s_Quad = Quad({0, 0}, {1, 1}, {1, 1, 1, 1});
static glm::vec4  s_Color = {1, 1, 1, 1};

static entt::entity* s_SelectedEntity = nullptr;

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

void ShowRendererStatistics() {
    ImGui::Begin("Renderer Statistics");
    ImGui::Text("Batch Count: %i", RendererStatistics::GetBatchCount());
    ImGui::End();
}

void EditorScene::Update(const float& deltaTime) {
    // Start ImGui Frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

//    ImGui::ShowDemoWindow();

//    ImGui::Begin("Test");
//
//    ImGui::ColorEdit3("Background Color", &m_GameContext->GetDisplay().GetBackgroundColor().r, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB);
//    ImGui::ColorEdit4("Quad Color", &s_Color.r, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB);
//
//    ImGui::End();

    RendererStatistics::Start();
    Renderer::StartBatch();

    Renderer::DrawQuad(s_Quad, s_Color);

    Renderer::EndBatch();
    RendererStatistics::Stop();

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
