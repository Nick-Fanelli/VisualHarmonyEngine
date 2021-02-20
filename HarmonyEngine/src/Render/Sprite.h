//
// Created by Nick Fanelli on 2/20/21.
//

#pragma once

#include "harmonypch.h"

namespace HarmonyEngine {

    class Sprite {
        Quad m_Quad;
        SpriteSheet* m_SpriteSheet;

    public:
        Sprite() = default;
        Sprite(const Sprite&) = default;
        Sprite(const Quad& quad, SpriteSheet* spriteSheet) : m_Quad(quad), m_SpriteSheet(spriteSheet) {}

    };
}