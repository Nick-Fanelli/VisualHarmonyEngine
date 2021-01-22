#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "Log.h"
#include <memory>
#include "Input.h"

class SceneManager;
class Scene;
class Display;

// ==========================================================================================
// Game Context Class Methods
// ==========================================================================================
class GameContext {

    friend class Display; 

    std::shared_ptr<Display> m_Display;
    std::shared_ptr<SceneManager> m_SceneManager;
    
    // Input m_Input;
    Input m_Input;

    int m_CurrentFps;

public:
    GameContext() : m_Input(Input()) {}

    void Start(Scene* scene);
    void Update(const float& deltaTime);
    void Stop();

    const int& GetCurrentFps() const { return m_CurrentFps; }
    Input& GetInput() { return m_Input; }
};
