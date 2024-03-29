//
// Created by Nick Fanelli on 3/16/21.
//

#include "RenderLayer.h"

#include <Scene/Component.h>

namespace HarmonyEditor {

    Scene* RenderLayer::s_Scene = nullptr;

    void RenderLayer::Initialize(Scene* scene) {
        s_Scene = scene;
        Renderer::OnCreate(&scene->GetCamera());
    }

    void RenderLayer::Begin() {
#ifdef HARMONY_DEBUG_ENABLED
        RendererStatistics::Start();
#endif

        Renderer::StartBatch();
    }

    void RenderLayer::End() {
        Renderer::EndBatch();

#ifdef HARMONY_DEBUG_ENABLED
        RendererStatistics::Stop();
#endif
    }

    void RenderLayer::Render() {
        auto quadRendererGroup = s_Scene->GetRegistry().group<QuadRenderer>(entt::get<Transform>);
        for (auto entity : quadRendererGroup) {
            auto[quadRenderer, transform] = quadRendererGroup.get<QuadRenderer, Transform>(entity);
            Renderer::DrawQuad(transform.Position, transform.Scale, quadRenderer.Color);
        }
    }

    void RenderLayer::CleanUp() {
        Renderer::OnDestroy();
    }

}