//
// Created by Nick Fanelli on 3/1/21.
//

#include "EditorScene.h"

#include "Hierarchy.h"

#include "Layers/ImGuiLayer.h"
#include "Layers/RenderLayer.h"

#include "Settings.h"

namespace HarmonyEditor {

    using namespace HarmonyEngine;

    static Hierarchy s_Hierarchy = Hierarchy();

    static entt::entity s_Entity;
    static Transform* s_Transform;
    static QuadRenderer* s_QuadRenderer;

    void EditorScene::OnCreate(GameContext* gameContext) {
        m_GameContext = gameContext;

        Settings::LoadSettings();

        RenderLayer::Initialize(this);
        ImGuiLayer::Initialize(gameContext);

        s_Entity = CreateGameObject();

        s_Transform = &Entity::AddComponent<Transform>(this, s_Entity, glm::vec2(-0.5, -0.5));
        s_QuadRenderer = &Entity::AddComponent<QuadRenderer>(this, s_Entity, glm::vec4(1, 1, 1, 1));

        s_Hierarchy.AddGameObject(s_Entity);

//        s_Entity = CreateGameObject();
//        s_Transform = &Entity::AddComponent<Transform>(this, s_Entity, glm::vec2(-0.5, -0.5));
//        s_QuadRenderer = &Entity::AddComponent<QuadRenderer>(this, s_Entity, glm::vec4(1, 1, 1, 1));
//
//        s_Hierarchy.AddGameObject(s_Entity);
    }

    void EditorScene::Update(const float& deltaTime) {

//        s_Transform->Position.x += deltaTime;

//        if(Input::StandardInput.IsKey(HARMONY_KEY_W))
//            s_Transform->Position.y += s_PlayerSpeed * deltaTime;
//        if(Input::StandardInput.IsKey(HARMONY_KEY_S))
//            s_Transform->Position.y -= s_PlayerSpeed * deltaTime;
//        if(Input::StandardInput.IsKey(HARMONY_KEY_A))
//            s_Transform->Position.x -= s_PlayerSpeed * deltaTime;
//        if(Input::StandardInput.IsKey(HARMONY_KEY_D))
//            s_Transform->Position.x += s_PlayerSpeed * deltaTime;

        ImGuiLayer::Begin();
        ImGuiLayer::Render();
        ImGuiLayer::End();

        RenderLayer::Begin();
        RenderLayer::Render();
        RenderLayer::End();
    }

    void EditorScene::OnDestroy() {
        RenderLayer::CleanUp();
        ImGuiLayer::CleanUp();
    }
}