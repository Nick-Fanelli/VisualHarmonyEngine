#pragma once

#include <GL/glew.h>
#include <GLUT/glut.h>

#include <GLFW/glfw3.h>

#include "Log.h"
#include "Input.h"
#include "Display.h"
#include "../Scene/Scene.h"

// ==========================================================================================
// Game Context Class Methods
// ==========================================================================================
class GameContext {

    friend class Display; 

    Display m_Display;
    SceneManager m_SceneManager;
    
    Input m_Input;
    Renderer m_Renderer;

    int m_CurrentFps;

public:
    GameContext() : m_Display(Display()), m_SceneManager(SceneManager(this)), m_Input(Input()), m_Renderer(Renderer()) {}

    void Start(Scene* scene);
    void Update(const float& deltaTime);
    void Stop();

    const int& GetCurrentFps() const { return m_CurrentFps; }
    Input& GetInput() { return m_Input; }
    Renderer& GetRenderer() { return m_Renderer; }
};
