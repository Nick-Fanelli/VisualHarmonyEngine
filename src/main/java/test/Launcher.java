package test;

import com.harmonygames.harmonyengine.GameContext;
import com.harmonygames.harmonyengine.scene.SceneManager;

import java.io.*;
import java.net.URISyntaxException;

public class Launcher {

    public static void main(String[] args) {
//        InputStream stream = Launcher.class.getResourceAsStream("/default/default.frag.glsl");
//        InputStreamReader reader = new InputStreamReader(stream);
//        BufferedReader bufferedReader = new BufferedReader(reader);
//
//        bufferedReader.lines().forEach(System.out::println);

        GameContext gameContext = new GameContext();
        gameContext.start(new TestScene());
    }

}
