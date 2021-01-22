#include "Display.h"
#include "Log.h"
#include "GameContext.h"

static GLuint startingWidth = 1280;
static GLuint startingHeight = 720;

void Display::CreateDisplay(GameContext* gameContext) {

    m_GameContext = gameContext;

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

    // Handle Input
    m_GameContext->GetInput().StandardInput.SetupKeyInputs(this); 

    if(glewInit() != GLEW_OK) {
        Log::Error("Could not initialize GLEW");
        return;
    }

    glViewport(0, 0, screenWidth, screenHeight);

    Log::Success("Created the GLFW dsiplay!");

    glfwFocusWindow(m_Window);
}

void Display::StartGameLoop() {
    Log::Info("Starting Game Loop");

    float endTime, startTime = (float) glfwGetTime();
    float deltaTime = -1.0f;

    double lastTime = glfwGetTime();
    double currentTime;
    int frameCount = 0;

    while(!glfwWindowShouldClose(m_Window)) {

        // Handle Input

        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if(deltaTime >= 0) {
            m_GameContext->Update(deltaTime);
            // m_SceneManager.Update(deltaTime);
        }

        glfwSwapBuffers(m_Window);
        glfwPollEvents();

        currentTime = glfwGetTime();
        frameCount++;

        if(currentTime - lastTime >= 1.0) {
            m_GameContext->m_CurrentFps = 1000.0 / double(frameCount);
            frameCount = 0;
            lastTime = glfwGetTime();
        }

        endTime = (float) glfwGetTime();
        deltaTime = endTime - startTime;
        startTime = endTime;
    }

    CleanUp();
}

void Display::CleanUp() {
    Log::Info("Cleaning up the program...");

    m_GameContext->Stop();

    glfwDestroyWindow(m_Window);
    glfwTerminate();

    Log::Success("Progam successfully exited!");
}