package test;

import com.harmonygames.harmonyengine.GameContext;
import com.harmonygames.harmonyengine.input.StandardInput;
import com.harmonygames.harmonyengine.object.GameObject;
import com.harmonygames.harmonyengine.object.component.SpriteRenderer;
import com.harmonygames.harmonyengine.render.Sprite;
import com.harmonygames.harmonyengine.render.Texture;
import com.harmonygames.harmonyengine.scene.Scene;
import org.lwjgl.glfw.GLFW;
import org.lwjgl.system.CallbackI;

public class TestScene extends Scene {

    private GameObject gameObject;
    private final float playerSpeed = 200f;

    @Override
    public void onCreate() {

        mainCamera.transform.position.set(0, 0);

        gameObject = new GameObject("Example Object");
        gameObject.transform.scale.set(32, 32);
        gameObject.transform.position.set(100, 100);

        SpriteRenderer renderer = new SpriteRenderer();
        gameObject.addComponent(renderer);
        Sprite sprite = new Sprite();
        sprite.setTexture(new Texture("/grass.jpg", gameObject.transform.scale));
        renderer.setSprite(sprite);

        super.addGameObject(gameObject);
        super.onCreate();
    }

    @Override
    public void update(float deltaTime) {
        super.update(deltaTime);

        if(StandardInput.isKeyPressed(GLFW.GLFW_KEY_UP)) {
            gameObject.transform.position.y += playerSpeed * deltaTime;
        }

        if(StandardInput.isKeyPressed(GLFW.GLFW_KEY_DOWN)) {
            gameObject.transform.position.y -= playerSpeed * deltaTime;
        }

        if(StandardInput.isKeyPressed(GLFW.GLFW_KEY_RIGHT)) {
            gameObject.transform.position.x += playerSpeed * deltaTime;
        }

        if(StandardInput.isKeyPressed(GLFW.GLFW_KEY_LEFT)) {
            gameObject.transform.position.x -= playerSpeed * deltaTime;
        }
    }

}