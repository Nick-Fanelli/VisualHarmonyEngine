#pragma once

#include <memory>
#include <array>

#include "RenderComponents.h"
#include "../Scene/Camera.h"

class Scene;

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

    Quad(const glm::vec2& position, const float& scale, const std::array<glm::vec4, 4> colorArray, const float& textureID) {
        V0.Position = position;
        V0.Color = colorArray[0];
        V0.TextureCoord = { 0, 0 };
        V0.TextureID = textureID;

        V1.Position = glm::vec2(position.x, position.y + 1 * scale);
        V1.Color = colorArray[1];
        V1.TextureCoord = { 0, 1 };
        V1.TextureID = textureID;

        V2.Position = glm::vec2(position.x + 1 * scale, position.y + 1 * scale);
        V2.Color = colorArray[2];
        V2.TextureCoord = { 1, 1 };
        V2.TextureID = textureID;

        V3.Position = glm::vec2(position.x + 1 * scale, position.y);
        V3.Color = colorArray[3];
        V3.TextureCoord = { 1, 0 };
        V3.TextureID = textureID;
    }

    // Quad(const glm::vec2& position, const float& scale, const std::array<glm::vec4, 4> colorArray) { Quad(position, scale, colorArray, 0.0f); }

};

class Renderer {

    OrthographicCamera* m_Camera = nullptr;

    std::unique_ptr<Shader> m_Shader;
    bool m_ShouldUpdateVertexData = true;
    
    void Render();
    void UpdateBatchVertexData();
    
public:
    // void GenerateQuad(const glm::vec2& position, const float& scale, const std::array<glm::vec4, 4> colorArray);
    // void GenerateQuad(const glm::vec2& position, const float& scale, const glm::vec4& color);
    // void GenerateQuad(const glm::vec2& position, const float& scale) { GenerateQuad(position, scale, glm::vec4(1, 1, 1, 1)); }
    // void GenerateQuad(const glm::vec2& position) { GenerateQuad(position, 1); } 
    Quad* AddQuad(const Quad& quad);

    void OnCreate(OrthographicCamera* camera);
    void Update(const float& deltaTime);
    void OnDestroy();

    void UpdateVertexData() { m_ShouldUpdateVertexData = true; }
};