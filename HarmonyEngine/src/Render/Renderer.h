#pragma once

#include <memory>
#include <array>

#include "RenderComponents.h"
#include "../Scene/Camera.h"

class Scene;

struct Vertex {

    glm::vec2 Position;
    glm::vec4 Color;
    
};

struct Quad {

    Vertex V0;
    Vertex V1;
    Vertex V2;
    Vertex V3;

    Quad(const glm::vec2& position, const float& scale, const std::array<glm::vec4, 4> colorArray) {
        V0.Position = position;
        V0.Color = colorArray[0];

        V1.Position = glm::vec2(position.x, position.y + 1 * scale);
        V1.Color = colorArray[1];

        V2.Position = glm::vec2(position.x + 1 * scale, position.y + 1 * scale);
        V2.Color = colorArray[2];

        V3.Position = glm::vec2(position.x + 1 * scale, position.y);
        V3.Color = colorArray[3];
    }

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