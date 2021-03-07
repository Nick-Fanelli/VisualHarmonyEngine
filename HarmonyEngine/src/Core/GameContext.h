#pragma once

#include <GL/glew.h>
#include <GLUT/glut.h>

#include <GLFW/glfw3.h>

#include "Display.h"
#include "../Scene/Scene.h"

namespace HarmonyEngine {

// ==========================================================================================
// Game Context Class Methods
// ==========================================================================================
    class GameContext {

        friend class Display;

        Display m_Display;
        SceneManager m_SceneManager;

        int m_CurrentFps;

    public:
        GameContext() : m_Display(Display()), m_SceneManager(SceneManager(this)) {}

        void Start(Scene* scene);
        void Update(const float& deltaTime);
        void Stop();

        const int& GetCurrentFps() const { return m_CurrentFps; }

        Display& GetDisplay() { return m_Display; }

    };

}