#include "GameContext.h"

#include "Log.h"
#include "Utils.h"
#include "../Render/Shader.h"
#include <string>

void GameContext::Start() {
    CreateDisplay();
    StartGameLoop();
}

void GameContext::Stop() {

}

static GLuint startingWidth = 1280;
static GLuint startingHeight = 720;

void GameContext::CreateDisplay() {

    Log::Info("Creating the display...");

    if(!glfwInit()) {
        Log::Error("Could not initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    m_Window = glfwCreateWindow(startingWidth, startingHeight, "HarmonyEngine", nullptr, nullptr);

    int screenWidth, screenHeight;

    glfwGetFramebufferSize(m_Window, &screenWidth, &screenHeight);

    if(m_Window == nullptr) {
        Log::Error("could not create the GLFW Window");
        glfwTerminate();

        return;
    }

    glfwMakeContextCurrent(m_Window);

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) {
        Log::Error("Could not initialize GLEW");
        return;
    }

    glViewport(0, 0, screenWidth, screenHeight);

    Log::Success("Created the GLFW dsiplay!");
}

// Test Triangle Drawing Code

static GLfloat vertices[] = {
    +0.0f, +0.8f,    // Top coordinate
    -0.8f, -0.8f,    // Bottom-left coordinate
    +0.8f, -0.8f     // Bottom-right coordinate
};

static GLfloat colors[] = {
    1, 0, 0, 1,  // Red color, for the first vertex
    0, 1, 0, 1,  // Green color, for the second vertex
    0, 0, 1, 1   // Blue color, for the third vertex
};

void GameContext::StartGameLoop() {
    Log::Info("Starting Game Loop");

    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW); // Might have to not use memory location

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    GLuint vboColorID;
    glGenBuffers(1, &vboColorID);
    glBindBuffer(GL_ARRAY_BUFFER, vboColorID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), &colors, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glBindVertexArray(0);

    // Load Shader
    std::string vertexData = FileUtils::ReadFile("HarmonyEngine/assets/default.vert.glsl");
    std::string fragmentData = FileUtils::ReadFile("HarmonyEngine/assets/default.frag.glsl");

    Shader shader = Shader(vertexData, fragmentData);

    while(!glfwWindowShouldClose(m_Window)) {

        // Handle Input

        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();

        glBindVertexArray(vaoID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);

        shader.Unbind();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    shader.Dispose();

    CleanUp();
}

void GameContext::CleanUp() {
    Log::Info("Cleaning up the program...");

    Stop();

    glfwDestroyWindow(m_Window);
    glfwTerminate();

    Log::Success("Progam successfully exited!");
}