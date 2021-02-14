#pragma once

// ======================================================================================
// Quad Renderer Component
// ======================================================================================
struct QuadRenderer {

    Quad quad;

    // QuadRenderer() = default;
    // QuadRenderer(const QuadRenderer&) = default;
    QuadRenderer(const Quad& quad) : quad(quad) {}
};