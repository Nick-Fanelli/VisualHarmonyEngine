#pragma once

// ======================================================================================
// Transform Component
// ======================================================================================

struct Transform {

    glm::vec2 Position;

    Transform() = default;
    Transform(const Transform&) = default;
    Transform(const glm::vec2& position) : Position(position) {}

};

// ======================================================================================
// Quad Renderer Component
// ======================================================================================
struct QuadRenderer {

    Quad quad;

    QuadRenderer() = default;
    QuadRenderer(const QuadRenderer&) = default;
    QuadRenderer(const Quad& quad) : quad(quad) {}
};