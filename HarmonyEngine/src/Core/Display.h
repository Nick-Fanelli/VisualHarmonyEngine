#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "harmonypch.h"

namespace HarmonyEngine {

    class GameContext;

    class Display {

        GLFWwindow* m_Window;
        GameContext* m_GameContext;

        glm::vec3 m_BackgroundColor = glm::vec3(0.1, 0.1, 0.1);

    public:
        void CreateDisplay(GameContext* gameContext);

        void StartGameLoop();

        GLFWwindow* GetWindowPointer() const { return m_Window; }
        const glm::vec3& GetBackgroundColor() const { return m_BackgroundColor; }
        glm::vec3& GetBackgroundColor() { return m_BackgroundColor; }

    private:
        void CleanUp();

    };
}