#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>

#define GLFW_DLL
#include <GLFW/glfw3.h>

// ==========================================================================================
// Game Context Class Methods
// ==========================================================================================
class GameContext {

    GLFWwindow* m_Window;

    void CreateDisplay();
    void StartGameLoop();
    void CleanUp(); 

public:
    void Start();
    void Stop();
};
