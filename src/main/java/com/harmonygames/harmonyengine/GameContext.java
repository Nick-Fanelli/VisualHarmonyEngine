package com.harmonygames.harmonyengine;

import com.harmonygames.harmonyengine.display.Display;

public class GameContext {

    private Display display;

    public void start() {
        display = new Display();
        display.init();

        while(display.shouldContinueRunning()) {
            display.update();
        }

        display.cleanUp();
    }

}
