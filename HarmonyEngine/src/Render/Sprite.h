#pragma once

#include "Renderer.h"

#include "Texture.h"

struct Sprite {

    Quad quad;
    const int& textureID;

    Sprite(const Sprite&) = default;
    Sprite(const Quad& quad, const int& texture) : quad(quad), textureID(texture) {}

};