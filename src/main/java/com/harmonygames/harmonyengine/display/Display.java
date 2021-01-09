package com.harmonygames.harmonyengine.display;

import com.harmonygames.harmonyengine.GameContext;
import com.harmonygames.harmonyengine.Log;
import com.harmonygames.harmonyengine.scene.SceneManager;
import org.lwjgl.glfw.Callbacks;
import org.lwjgl.glfw.GLFW;
import org.lwjgl.glfw.GLFWErrorCallback;
import org.lwjgl.glfw.GLFWVidMode;
import org.lwjgl.opengl.GL;
import org.lwjgl.opengl.GL11;
import org.lwjgl.system.MemoryStack;
import org.lwjgl.system.MemoryUtil;

import java.nio.IntBuffer;
import java.util.Objects;

public class Display {

    // Window Pointer Address
    private long window;

    private final GameContext gameContext;
    private SceneManager sceneManager;

    public Display(GameContext gameContext) {
        this.gameContext = gameContext;
    }

    public void init() {
        GLFWErrorCallback.createPrint(System.err).set();

        // TODO: Use custom log method and assertions
        Log.info("Setting up GLFW...");
        if(!GLFW.glfwInit()) {
            Log.error("Unable to initialize GLFW");
            System.exit(-1);
        }
        Log.success("Setup GLFW");

        // Configure GLFW
        Log.info("Configuring GLFW...");
        GLFW.glfwDefaultWindowHints();

        GLFW.glfwWindowHint(GLFW.GLFW_CONTEXT_VERSION_MAJOR, 3);
        GLFW.glfwWindowHint(GLFW.GLFW_CONTEXT_VERSION_MINOR, 2);
        GLFW.glfwWindowHint(GLFW.GLFW_OPENGL_PROFILE, GLFW.GLFW_OPENGL_CORE_PROFILE);
        GLFW.glfwWindowHint(GLFW.GLFW_OPENGL_FORWARD_COMPAT, GLFW.GLFW_TRUE);
        GLFW.glfwWindowHint(GLFW.GLFW_VISIBLE, GLFW.GLFW_FALSE);
        GLFW.glfwWindowHint(GLFW.GLFW_RESIZABLE, GLFW.GLFW_TRUE);


        Log.success("Configured GLFW");

        // Create the window pointer object
        Log.info("Creating GLFW Window...");
        window = GLFW.glfwCreateWindow(1280, 720, "Harmony Engine", MemoryUtil.NULL, MemoryUtil.NULL);
        if(window == MemoryUtil.NULL) {
            Log.error("Failed to create the GLFW window");
            System.exit(-1);
        }
        Log.success("Created GLFW window!");

        // Setup callbacks/inputs
        // TODO: Remove
        GLFW.glfwSetKeyCallback(window, (window, key, scancode, action, mods) -> {
            if(key == GLFW.GLFW_KEY_ESCAPE && action == GLFW.GLFW_RELEASE)
                GLFW.glfwSetWindowShouldClose(window, true);
        });

        try(MemoryStack stack = MemoryStack.stackPush()) {
            IntBuffer pWidth  = stack.mallocInt(1); // int pointer
            IntBuffer pHeight = stack.mallocInt(1); // int pointer

            // Get the original window size
            GLFW.glfwGetWindowSize(window, pWidth, pHeight);

            // Get the resolution of the primary monitor
            GLFWVidMode vidMode = GLFW.glfwGetVideoMode(GLFW.glfwGetPrimaryMonitor());

            assert vidMode != null;

            // Center the window in the primary monitor
            GLFW.glfwSetWindowPos(window,
                    (vidMode.width() - pWidth.get(0)) / 2,
                    (vidMode.height() - pHeight.get(0)) / 2);
        }

        // Make the OpenGL context to the current window
        GLFW.glfwMakeContextCurrent(window);
        // TODO: Make a preference
        // Enable v-sync
        GLFW.glfwSwapInterval(1);

        // Show the window
        GLFW.glfwFocusWindow(window);
        GLFW.glfwShowWindow(window);

        GL.createCapabilities(); // Very important for OpenGL.

        // TODO: Make a preference
        // Clear the screen
        GL11.glClearColor(0, 0, 0, 1.0f);

        this.sceneManager = new SceneManager();
    }

    public void loop() {
        float endTime, beginTime = (float) GLFW.glfwGetTime();
        float deltaTime = -1f;

        while(!GLFW.glfwWindowShouldClose(window)) {

//            GL11.glClearColor(0, 0, 0, 1f);
            GL11.glClear(GL11.GL_COLOR_BUFFER_BIT | GL11.GL_DEPTH_BUFFER_BIT);

            if(deltaTime >= 0) {
                sceneManager.update(deltaTime);
            }

            GLFW.glfwSwapBuffers(window);
            GLFW.glfwPollEvents();

            endTime = (float) GLFW.glfwGetTime();
            deltaTime = endTime - beginTime;
            beginTime = endTime;
        }
    }

    public void update() {
        // Clear the screen
        GL11.glClear(GL11.GL_COLOR_BUFFER_BIT | GL11.GL_DEPTH_BUFFER_BIT);

        // Swap the color buffers
        GLFW.glfwSwapBuffers(window);

        // Check poll or window events eg. input
        GLFW.glfwPollEvents();
    }

    public void cleanUp() {
        // Free and clean up the window
        Callbacks.glfwFreeCallbacks(window);
        GLFW.glfwDestroyWindow(window);

        // Terminate GLFW
        GLFW.glfwTerminate();
        Objects.requireNonNull(GLFW.glfwSetErrorCallback(null)).free();
    }

    public boolean shouldContinueRunning() { return !GLFW.glfwWindowShouldClose(window); }
    public long getWindow() { return this.window; }

}
