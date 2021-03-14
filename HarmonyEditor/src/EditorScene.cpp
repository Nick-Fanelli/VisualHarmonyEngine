//
// Created by Nick Fanelli on 3/1/21.
//

#include "EditorScene.h"

#include "EditorLayers.h"

#include "Hierarchy.h"

using namespace HarmonyEngine;

static Hierarchy s_Hierarchy = Hierarchy();
static entt::entity s_Entity;

static QuadRenderer* s_QuadRenderer;

void EditorScene::OnCreate(GameContext* gameContext) {
    m_GameContext = gameContext;

    RenderLayer::Initialize(this);
    ImGuiLayer::Initialize(gameContext);

    s_Entity = CreateGameObject();
    Entity::AddComponent<Transform>(this, s_Entity, glm::vec2(-0.5, -0.5));
    s_QuadRenderer = &Entity::AddComponent<QuadRenderer>(this, s_Entity, glm::vec4(1, 1, 1, 1));

    s_Hierarchy.AddGameObject(s_Entity);
}

//void ShowRendererStatistics() {
//    ImGui::Begin("Renderer Statistics");
//
//    ImGui::Text("Batch Count: %zu", RendererStatistics::GetBatchCount());
//    ImGui::Text("Vertex Count: %zu", RendererStatistics::GetVertexCount());
//    ImGui::Text("Index Count: %zu", RendererStatistics::GetIndexCount());
//
//    ImGui::End();
//}

void EditorScene::Update(const float& deltaTime) {
    if(Input::StandardInput.IsKeyUp(HARMONY_KEY_A)) Log::Info("A");

    ImGuiLayer::RenderImGuiWindows();
    RenderLayer::RenderScene();
}

void EditorScene::OnDestroy() {
    RenderLayer::CleanUp();
    ImGuiLayer::CleanUp();
}
