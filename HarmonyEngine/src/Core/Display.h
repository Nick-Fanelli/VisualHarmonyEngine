#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLUT/glut.h>

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <iostream>

namespace HarmonyEngine {

    class GameContext;

    class Display {

        GLFWwindow* m_Window;
        GameContext* m_GameContext;

    public:
        void CreateDisplay(GameContext* gameContext);

        void StartGameLoop();

        GLFWwindow* GetWindowPointer() const { return m_Window; }

    private:
        void CleanUp();

    };
}