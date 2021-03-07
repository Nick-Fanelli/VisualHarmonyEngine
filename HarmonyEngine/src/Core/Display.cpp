#include "Display.h"

#include "GameContext.h"
#include "Input.h"

namespace HarmonyEngine {

    static int startingWidth = 1280;
    static int startingHeight = 720;

    void Display::CreateDisplay(GameContext* gameContext) {

        m_GameContext = gameContext;

        Log::Info("Creating the display...");

        if (!glfwInit()) {
            HARMONY_ASSERT("Could not initialize GLFW")
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        m_Window = glfwCreateWindow(startingWidth, startingHeight, "HarmonyEngine", nullptr, nullptr);

        int screenWidth, screenHeight;

        glfwGetFramebufferSize(m_Window, &screenWidth, &screenHeight);

        if (m_Window == nullptr) {
            glfwTerminate();
            HARMONY_ASSERT("Could not create the GLFW Window")
            return;
        }

        glfwMakeContextCurrent(m_Window);
        glewExperimental = GL_TRUE;

        // Handle Input
        Input::StandardInput.SetupKeyInputs(this);

        if (glewInit() != GLEW_OK) {
            HARMONY_ASSERT("Could not initialize GLEW")
            return;
        }

        glViewport(0, 0, screenWidth, screenHeight);

        // glDebugMessageCallback(GL_DEBUG_CALLBACK_FUNCTION, )

        Log::Success("Created the GLFW display!");

        glfwFocusWindow(m_Window);
    }

    void Display::StartGameLoop() {
        Log::Info("Starting Game Loop");

        float endTime, startTime = (float) glfwGetTime();
        float deltaTime = -1.0f;

        double lastTime = glfwGetTime();
        double currentTime;
        int frameCount = 0;

        while (!glfwWindowShouldClose(m_Window)) {

            glClearColor(m_BackgroundColor.x, m_BackgroundColor.y, m_BackgroundColor.z, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            if (deltaTime >= 0) {
                m_GameContext->Update(deltaTime);

                Input::Update();
            }

            glfwSwapBuffers(m_Window);
            glfwPollEvents();

            currentTime = glfwGetTime();
            frameCount++;

            if (currentTime - lastTime >= 1.0) {
                m_GameContext->m_CurrentFps = 1000 / frameCount;
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

        Log::Success("Program successfully exited!");
    }
}