//
// Created by Nick Fanelli on 3/14/21.
//

#include "EditorLayers.h"

#include <Scene/Component.h>

// ================================================================================
// Render Layer
// ================================================================================

void RenderLayer::Initialize(Scene* scene) {
    s_Scene = scene;
    Renderer::OnCreate(&scene->GetCamera());
}

void RenderLayer::RenderScene() {
#ifdef HARMONY_DEBUG_ENABLED
    RendererStatistics::Start();
#endif

    Renderer::StartBatch();

    auto quadRendererGroup = s_Scene->GetRegistry().group<QuadRenderer>(entt::get<Transform>);
    for(auto entity : quadRendererGroup) {
        auto[quadRenderer, transform] = quadRendererGroup.get<QuadRenderer, Transform>(entity);
        Renderer::DrawQuad(transform.Position, transform.Scale, quadRenderer.Color);
    }

//    Renderer::DrawQuad(s_Quad, s_Color);

    Renderer::EndBatch();

#ifdef HARMONY_DEBUG_ENABLED
    RendererStatistics::Stop();
#endif
}

void RenderLayer::CleanUp() {
    Renderer::OnDestroy();
}

// ================================================================================
// ImGui Layer
// ================================================================================

void ImGuiLayer::Initialize(GameContext* gameContextPtr) {

    const char* glsl_version = "#version 150";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void) io;

//    ImGui::StyleColorsDark();
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);

    ImGui_ImplGlfw_InitForOpenGL(gameContextPtr->GetDisplay().GetWindowPointer(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

}

void ImGuiLayer::RenderImGuiWindows() {
    // Start ImGui Frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Do Stuff
    ImGui::ShowDemoWindow();

//    ImGui::Begin("Inspector");
//    ImGui::ColorEdit3("Quad Color", &s_QuadRenderer->Color.r, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB);
//    ImGui::End();

    // End ImGui Frame
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::CleanUp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}