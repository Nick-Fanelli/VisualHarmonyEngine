#include "GameContext.h"

void GameContext::Start(Scene* scene) {
    CreateDisplay(scene);
    StartGameLoop();
}

void GameContext::Stop() {
    m_SceneManager.OnDestroy();
}

static GLuint startingWidth = 1280;
static GLuint startingHeight = 720;

void GameContext::CreateDisplay(Scene* scene) {

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

    m_SceneManager = SceneManager();
    Log::Success("Created the GLFW dsiplay!");
    SceneManager::SetActiveScene(scene);
}

void GameContext::StartGameLoop() {
    Log::Info("Starting Game Loop");

    float endTime, startTime = (float) glfwGetTime();
    float deltaTime = -1.0f;

    while(!glfwWindowShouldClose(m_Window)) {

        // Handle Input

        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if(deltaTime >= 0) {
            m_SceneManager.Update(deltaTime);
        }

        glfwSwapBuffers(m_Window);
        glfwPollEvents();

        endTime = (float) glfwGetTime();
        deltaTime = endTime - startTime;
        startTime = endTime;
    }

    CleanUp();
}

void GameContext::CleanUp() {
    Log::Info("Cleaning up the program...");

    Stop();

    glfwDestroyWindow(m_Window);
    glfwTerminate();

    Log::Success("Progam successfully exited!");
}