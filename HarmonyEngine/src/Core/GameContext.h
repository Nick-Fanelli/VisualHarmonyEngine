#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "Log.h"
#include "../Scene/Scene.h"

class Display;

// ==========================================================================================
// Game Context Class Methods
// ==========================================================================================
class GameContext {

    Display* m_Display;
    SceneManager m_SceneManager;

public:
    void Start(Scene* scene);
    void Update(const float& deltaTime);
    void Stop();
};
