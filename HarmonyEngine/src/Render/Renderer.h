#pragma once

#include <memory>
#include <array>

#include "Texture.h"
#include "../Scene/Camera.h"
#include "Shader.h"

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

    Vertex() = default;

};

struct Quad {

    Vertex V0;
    Vertex V1;
    Vertex V2;
    Vertex V3;

    Quad() = default;

    Quad(const glm::vec2& offset, const glm::vec2& scale = {1, 1 }, const std::array<glm::vec4, 4> colorArray = DefaultWhiteColor, const int& textureID = 0) {
        V0.Position = offset;
        V0.Color = colorArray[0];
        V0.TextureCoord = { 0, 0 };
        V0.TextureID = (float) textureID;

        V1.Position = glm::vec2(offset.x, offset.y + 1 * scale.y);
        V1.Color = colorArray[1];
        V1.TextureCoord = { 0, 1 };
        V1.TextureID = (float) textureID;

        V2.Position = glm::vec2(offset.x + 1 * scale.x, offset.y + 1 * scale.y);
        V2.Color = colorArray[2];
        V2.TextureCoord = { 1, 1 };
        V2.TextureID = (float) textureID;

        V3.Position = glm::vec2(offset.x + 1 * scale.x, offset.y);
        V3.Color = colorArray[3];
        V3.TextureCoord = { 1, 0 };
        V3.TextureID = (float) textureID;
    }

    Quad(const glm::vec2& offset, const glm::vec2& scale = {1, 1 }, const glm::vec4 color = {1, 1, 1, 1 }, const int& textureID = 0) {
        V0.Position = offset;
        V0.Color = color;
        V0.TextureCoord = { 0, 0 };
        V0.TextureID = (float) textureID;

        V1.Position = glm::vec2(offset.x, offset.y + 1 * scale.y);
        V1.Color = color;
        V1.TextureCoord = { 0, 1 };
        V1.TextureID = (float) textureID;

        V2.Position = glm::vec2(offset.x + 1 * scale.x, offset.y + 1 * scale.y);
        V2.Color = color;
        V2.TextureCoord = { 1, 1 };
        V2.TextureID = (float) textureID;

        V3.Position = glm::vec2(offset.x + 1 * scale.x, offset.y);
        V3.Color = color;
        V3.TextureCoord = { 1, 0 };
        V3.TextureID = (float) textureID;
    }
};

class Renderer {

    static void Render();
    static void UpdateBatchVertexData();
    static void AllocateVertices(const int& amount);

public:
    static const int& AddTexture(const Texture& texture);

    static void OnCreate(OrthographicCamera* camera);
    static void StartBatch();
    static void EndBatch();
    static void OnDestroy();

    static void DrawQuad(const Quad& quad);
    static void DrawQuad(const glm::vec2& positionOffset, const Quad& quad);
    static void DrawQuad(const glm::vec2& position = { 0, 0 }, const glm::vec2& scale = { 1, 1 }, const glm::vec4& color = { 1, 1, 1, 1 }, const float& textureID = 0);
    static void DrawQuad(const glm::vec2& position = { 0, 0 }, const glm::vec2& scale = { 1, 1 }, const std::array<glm::vec4, 4>& colorArray = DefaultWhiteColor, const float& textureID = 0);
};