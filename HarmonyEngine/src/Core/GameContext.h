#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "Log.h"
#include "../Scene/Scene.h"

// ==========================================================================================
// Game Context Class Methods
// ==========================================================================================
class GameContext {

    GLFWwindow* m_Window;
    SceneManager m_SceneManager;

    void CreateDisplay(Scene* scene);
    void StartGameLoop();
    void CleanUp(); 

public:
    void Start(Scene* scene);
    void Stop();
};
