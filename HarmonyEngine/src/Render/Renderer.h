#pragma once

#include <array>
#include <vector>
#include <memory>
#include "RenderComponents.h"
#include <iostream>

class Scene;

class Renderer {

    Scene* m_Scene;
    std::unique_ptr<Shader> m_Shader;

public:
    Renderer(Scene* scene) : m_Scene(scene) {}

    void OnCreate();
    void Update(const float& deltaTime);
    void OnDestroy();
};