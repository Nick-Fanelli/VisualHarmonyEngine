#include "Display.h"

static GLFWwindow* window;

static GLuint startingWidth = 1280;
static GLuint startingHeight = 720;

void CreateDisplay() {
    if(!glfwInit()) {
        // TODO: Log error
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(startingWidth, startingHeight, "HarmonyEngine", nullptr, nullptr);

    int screenWidth, screenHeight;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if(window == nullptr) {
        // TODO: Log Error
        glfwTerminate();

        return;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) {
        // TODO: Log Error
        return;
    }

    glViewport(0, 0, screenWidth, screenHeight);

    // TODO: Log Success
}

void StartGameLoop() {
    while(!glfwWindowShouldClose(window)) {

        // Handle Input

        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    CleanUp();
}

void CleanUp() {
    glfwDestroyWindow(window);
    glfwTerminate();
}