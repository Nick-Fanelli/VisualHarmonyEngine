#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "Log.h"

class SceneManager;
class Scene;
class Display;

// ==========================================================================================
// Game Context Class Methods
// ==========================================================================================
class GameContext {

    friend class Display; 

    Display* m_Display;
    SceneManager* m_SceneManager;
    int m_CurrentFps;

public:
    GameContext() {}

    void Start(Scene* scene);
    void Update(const float& deltaTime);
    void Stop();

    const int& GetCurrentFps() const { return m_CurrentFps; }
};
