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

};

struct Quad {

    Vertex V0;
    Vertex V1;
    Vertex V2;
    Vertex V3;

    Quad(const glm::vec2& position, const glm::vec2& scale = { 1, 1 }, const std::array<glm::vec4, 4> colorArray = DefaultWhiteColor, const float& textureID = 0);
    Quad(const glm::vec2& position, const glm::vec2& scale = { 1, 1 }, const glm::vec4 color = { 1, 1, 1, 1 }, const float& textureID = 0);
};

class Renderer {

    OrthographicCamera* m_Camera = nullptr;

    std::unique_ptr<Shader> m_Shader;
    
    void Render();
    void UpdateBatchVertexData();
    void AllocateVertices(const int& amount);

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