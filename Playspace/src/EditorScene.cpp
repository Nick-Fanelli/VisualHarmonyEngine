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

static Hierarchy s_Hierarchy = Hierarchy();
static entt::entity s_Entity;

static QuadRenderer* s_QuadRenderer;

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
    s_QuadRenderer = &Entity::AddComponent<QuadRenderer>(this, s_Entity, glm::vec4(1, 1, 1, 1));

    s_Hierarchy.AddGameObject(s_Entity);
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

    ImGui::Begin("Inspector");
    ImGui::ColorEdit3("Quad Color", &s_QuadRenderer->Color.r, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB);
    ImGui::End();

    // Input/Movement

    if(Input::StandardInput.IsKeyUp(HARMONY_KEY_A)) Log::Info("A");

    // Render Stuff
    RendererStatistics::Start();
    Renderer::StartBatch();

    auto quadRendererGroup = m_Registry.group<QuadRenderer>(entt::get<Transform>);
    for(auto entity : quadRendererGroup) {
        auto[quadRenderer, transform] = quadRendererGroup.get<QuadRenderer, Transform>(entity);
        Renderer::DrawQuad(transform.Position, transform.Scale, quadRenderer.Color);
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
