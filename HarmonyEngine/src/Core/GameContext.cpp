#include "GameContext.h"

#include <iostream>

// ==========================================================================================
// Game Context Class Methods
// ==========================================================================================
void GameContext::Start() {
    CreateDisplay();
    StartGameLoop();
}

void GameContext::Stop() {

}

static GLuint startingWidth = 1280;
static GLuint startingHeight = 720;

void GameContext::CreateDisplay() {

    if(!glfwInit()) {
        // TODO: Log error
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    m_Window = glfwCreateWindow(startingWidth, startingHeight, "HarmonyEngine", nullptr, nullptr);

    int screenWidth, screenHeight;

    glfwGetFramebufferSize(m_Window, &screenWidth, &screenHeight);

    if(m_Window == nullptr) {
        // TODO: Log Error
        glfwTerminate();

        return;
    }

    glfwMakeContextCurrent(m_Window);

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) {
        // TODO: Log Error
        return;
    }

    glViewport(0, 0, screenWidth, screenHeight);

    // TODO: Log Success
}

void GameContext::StartGameLoop() {
    while(!glfwWindowShouldClose(m_Window)) {

        // Handle Input

        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    CleanUp();
}

void GameContext::CleanUp() {
    Stop();

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}