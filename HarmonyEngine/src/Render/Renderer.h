#pragma once

#include <memory>

#include "RenderComponents.h"
#include "../Scene/Camera.h"

class Scene;

class Renderer {

    OrthographicCamera* m_Camera = nullptr;

    std::unique_ptr<Shader> m_Shader;
    
public:
    void OnCreate(OrthographicCamera* camera);
    void Render();
    void OnDestroy();
};