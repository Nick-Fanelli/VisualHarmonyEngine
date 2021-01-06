package com.harmonygames.harmonyengine;

import com.harmonygames.harmonyengine.display.Display;
import com.harmonygames.harmonyengine.scene.SceneManager;

public class GameContext {

    private SceneManager sceneManager;
    private Display display;

    private static int currentFps = 60;

    public void start() {
        display = new Display();
        display.init();

        sceneManager = new SceneManager();

        this.loop();
    }

    private void loop() {
        Log.info("Starting game loop");

        int frameCount = 0;
        double lastFrameTimeMills = System.currentTimeMillis();

        float deltaTime = 1f / 120f;
        double endTime, startTime = System.nanoTime() / 1E9;

        while(display.shouldContinueRunning()) {

            display.update();
            sceneManager.update(deltaTime);

            // Handle all the delta and frame stuff
            endTime = System.nanoTime() / 1E9;
            deltaTime = (float) (endTime - startTime);
            startTime = endTime;

            frameCount++;

            if(System.currentTimeMillis() - lastFrameTimeMills >= 1000) {
                currentFps = frameCount;
                lastFrameTimeMills = System.currentTimeMillis();
                frameCount = 0;
            }

        }

        this.cleanUp();
    }

    private void cleanUp() {
        Log.info("Cleaning up data...");
        display.cleanUp();
        Log.success("Finished cleaning up, application closed.");
    }

    public static int getCurrentFps() { return currentFps; }
}
