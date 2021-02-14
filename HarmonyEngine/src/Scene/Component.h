#pragma once

#include "../Render/Sprite.h"

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

    QuadRenderer(const QuadRenderer&) = default;
    QuadRenderer(const Quad& quad) : quad(quad) {}
};

// ======================================================================================
// Sprite Renderer Component
// ======================================================================================
struct SpriteRenderer {

    Sprite sprite;

    SpriteRenderer(const SpriteRenderer&) = default;
    SpriteRenderer(const Sprite& sprite) : sprite(sprite) {}

    // operator const Sprite&() const { return sprite; }
};