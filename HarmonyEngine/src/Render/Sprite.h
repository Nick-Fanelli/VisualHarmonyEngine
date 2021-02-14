#pragma once

#include "Renderer.h"

#include "Texture.h"

struct Sprite {

    Quad quad;
    Texture texture;

    Sprite() = default;
    Sprite(const Sprite&) = default;
    Sprite(const Quad& quad, const Texture& texture) : quad(quad), texture(texture) {}

};