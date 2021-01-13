package com.harmonygames.harmonyengine;

import com.harmonygames.harmonyengine.display.Display;
import com.harmonygames.harmonyengine.scene.Scene;
import com.harmonygames.harmonyengine.scene.SceneManager;
import org.lwjgl.opengl.GL;

public class GameContext {

    private Display display;
    private Scene scene;

    private static int currentFps = 60;

    public void start(Scene scene) {
        this.scene = scene;

        display = new Display(this);
        display.init();

        SceneManager.setActiveScene(scene);

        display.loop(); // Start the game loop
        this.cleanUp();
    }

    private void cleanUp() {
        Log.info("Cleaning up data...");
        display.cleanUp();
        Log.success("Finished cleaning up, application closed.");
    }

    public static int getCurrentFps() { return currentFps; }
}
