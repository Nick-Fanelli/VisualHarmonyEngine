#include "GameContext.h"

#include "Log.h"
#include "Utils.h"
#include "../Render/Shader.h"
#include "../Render/Mesh.h"
#include <string>
#include <vector>

void GameContext::Start() {
    CreateDisplay();
    StartGameLoop();
}

void GameContext::Stop() {

}

static GLuint startingWidth = 1280;
static GLuint startingHeight = 720;

void GameContext::CreateDisplay(){

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

static std::vector<float> vertices = {
     -0.5f, 0.5f,    // Left top         ID: 0
     -0.5f, -0.5f,   // Left bottom      ID: 1
     0.5f, -0.5f,    // Right bottom     ID: 2
     0.5f, 0.5f      // Right left       ID: 3
};

static std::vector<unsigned int> indices = { 
    // Left bottom triangle
            0, 1, 2,
            // Right top triangle
            2, 3, 0
};

static std::vector<float> colors = {
    1, 0, 0, 1,  // Red color, for the first vertex
    0, 1, 0, 1,  // Green color, for the second vertex
    0, 0, 1, 1   // Blue color, for the third vertex
};

void GameContext::StartGameLoop() {
    Log::Info("Starting Game Loop");

    Mesh2D mesh(vertices, indices);

    // Get the default mesh shader
    Shader shader = Shader::GetDefaultMeshShader();

    while(!glfwWindowShouldClose(m_Window)) {

        // Handle Input

        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // shader.Bind();

        // glBindVertexArray(mesh.GetVaoID());
        // glEnableVertexAttribArray(0);
        // // glEnableVertexAttribArray(1);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.GetEboID());

        // glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // glDisableVertexAttribArray(0);
        // // glDisableVertexAttribArray(1);
        // glBindVertexArray(0);

        // shader.Unbind();

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