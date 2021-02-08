#pragma once

#include <memory>
#include <array>

#include "Texture.h"
#include "RenderComponents.h"
#include "../Scene/Camera.h"

class Scene;

static const std::array<glm::vec4, 4> DefaultWhiteColor = {
    glm::vec4(1, 1, 1, 1),
    glm::vec4(1, 1, 1, 1),
    glm::vec4(1, 1, 1, 1),
    glm::vec4(1, 1, 1, 1)
};

struct Vertex {

    glm::vec2 Position;
    glm::vec4 Color;
    glm::vec2 TextureCoord;
    float TextureID;

};

struct Quad {

    Vertex V0;
    Vertex V1;
    Vertex V2;
    Vertex V3;

    Quad(const glm::vec2& position, const glm::vec2& scale = { 1, 1 }, const std::array<glm::vec4, 4> colorArray = DefaultWhiteColor, const float& textureID = 0) {
        V0.Position = position;
        V0.Color = colorArray[0];
        V0.TextureCoord = { 0, 0 };
        V0.TextureID = textureID;

        V1.Position = glm::vec2(position.x, position.y + 1 * scale.y);
        V1.Color = colorArray[1];
        V1.TextureCoord = { 0, 1 };
        V1.TextureID = textureID;

        V2.Position = glm::vec2(position.x + 1 * scale.x, position.y + 1 * scale.y);
        V2.Color = colorArray[2];
        V2.TextureCoord = { 1, 1 };
        V2.TextureID = textureID;

        V3.Position = glm::vec2(position.x + 1 * scale.x, position.y);
        V3.Color = colorArray[3];
        V3.TextureCoord = { 1, 0 };
        V3.TextureID = textureID;
    }

    Quad(const glm::vec2& position, const glm::vec2& scale = { 1, 1 }, const glm::vec4 color = { 1, 1, 1, 1 }, const float& textureID = 0) {
        V0.Position = position;
        V0.Color = color;
        V0.TextureCoord = { 0, 0 };
        V0.TextureID = textureID;

        V1.Position = glm::vec2(position.x, position.y + 1 * scale.y);
        V1.Color = color;
        V1.TextureCoord = { 0, 1 };
        V1.TextureID = textureID;

        V2.Position = glm::vec2(position.x + 1 * scale.x, position.y + 1 * scale.y);
        V2.Color = color;
        V2.TextureCoord = { 1, 1 };
        V2.TextureID = textureID;

        V3.Position = glm::vec2(position.x + 1 * scale.x, position.y);
        V3.Color = color;
        V3.TextureCoord = { 1, 0 };
        V3.TextureID = textureID;
    }

};

class Renderer {

    OrthographicCamera* m_Camera = nullptr;

    std::unique_ptr<Shader> m_Shader;
    
    void Render();
    void UpdateBatchVertexData();
    
public:
    const int& AddTexture(const Texture& texture);

    void OnCreate(OrthographicCamera* camera);
    void StartBatch();
    void EndBatch();
    void OnDestroy();

    void DrawQuad(const Quad& quad);
    void DrawQuad(const glm::vec2& position = { 0, 0 }, const glm::vec2& scale = { 1, 1 }, const glm::vec4& color = { 1, 1, 1, 1 }, const float& textureID = 0);
    void DrawQuad(const glm::vec2& position = { 0, 0 }, const glm::vec2& scale = { 1, 1 }, const std::array<glm::vec4, 4>& colorArray = DefaultWhiteColor, const float& textureID = 0);
};