package test;

import com.harmonygames.harmonyengine.GameContext;
import com.harmonygames.harmonyengine.scene.SceneManager;

public class Launcher {

    public static void main(String[] args) {
        GameContext gameContext = new GameContext();
        gameContext.start(new TestScene());
    }

}
