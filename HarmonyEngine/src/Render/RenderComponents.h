#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "../Scene/Component.h"
#include "Shader.h"
#include "Sprite.h"

// ======================================================================================
// Sprite Renderer Component
// ======================================================================================
class SpriteRenderer : public Component {

    Sprite* m_Sprite;
    glm::vec4 m_Color;

public:
    SpriteRenderer(Sprite* sprite) : m_Sprite(sprite), m_Color(glm::vec4(1, 1, 1, 1)) {}

    Sprite* GetSprite() const { return m_Sprite; }
    void SetSprite(Sprite* sprite) { m_Sprite = sprite; }

    const glm::vec4& GetColor() const { return m_Color; }
    void SetColor(glm::vec4 color) { m_Color = color; }
};