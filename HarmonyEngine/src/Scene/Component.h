#pragma once

namespace HarmonyEngine {

    // ======================================================================================
    // Transform Component
    // ======================================================================================
    struct Transform {

        glm::vec2 Position;
        glm::vec2 Scale;
        float Rotation;

        Transform() = default;
        Transform(const Transform&) = default;

        Transform(const glm::vec2& position, const glm::vec2& scale = {1, 1}, const float& rotation = 0.0f)
            : Position(position), Scale(scale), Rotation(rotation) {}

    };

    // ======================================================================================
    // Quad Renderer Component
    // ======================================================================================
    struct QuadRenderer {

        glm::vec4 Color;

        QuadRenderer() = default;
        QuadRenderer(const QuadRenderer&) = default;
    };
}