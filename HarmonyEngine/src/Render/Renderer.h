#pragma once

#include <array>
#include <vector>
#include <memory>
#include "RenderComponents.h"
#include <iostream>

class Renderer {

    std::unique_ptr<Shader> m_Shader;

public:
    Renderer() {}
    ~Renderer();

    void OnCreate();
    void Update(const float& deltaTime);
    void OnDestroy();
};