//
// Created by Nick Fanelli on 3/1/21.
//

#include "EditorScene.h"
#include "harmonypch.h"

#include "Hierarchy.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace HarmonyEngine;

static Quad s_Quad = Quad({0, 0}, {1, 1}, {1, 1, 1, 1});
static glm::vec4  s_Color = {1, 1, 1, 1};

static Hierarchy s_Hierarchy = Hierarchy();
static entt::entity s_Entity;

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

    s_Entity = CreateGameObject();

    Entity::AddComponent<Transform>(this, s_Entity, glm::vec2(-0.5, -0.5));
    Entity::AddComponent<QuadRenderer>(this, s_Entity, s_Quad);
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

//    Log::Info(s_Entity);

//    Log::Info(s_Hierarchy.RootNode.Children.at(1).Entity);

//    ImGui::ShowDemoWindow();

//    ImGui::Begin("Test");
//
//    ImGui::ColorEdit3("Background Color", &m_GameContext->GetDisplay().GetBackgroundColor().r, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB);
//    ImGui::ColorEdit4("Quad Color", &s_Color.r, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB);
//
//    ImGui::End();

    ImGui::Begin("Inspector");

    ImGui::ColorEdit3("Quad Color", &s_Color.r, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB);

    ImGui::End();

    RendererStatistics::Start();
    Renderer::StartBatch();

    auto quadRendererGroup = m_Registry.group<QuadRenderer>(entt::get<Transform>);
    for(auto entity : quadRendererGroup) {
        auto[quadRenderer, transform] = quadRendererGroup.get<QuadRenderer, Transform>(entity);\
        Renderer::DrawQuad(transform.Position, {1, 1}, s_Color);
    }

//    Renderer::DrawQuad(s_Quad, s_Color);

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
