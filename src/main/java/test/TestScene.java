package test;

import com.harmonygames.harmonyengine.object.GameObject;
import com.harmonygames.harmonyengine.object.component.SpriteRenderer;
import com.harmonygames.harmonyengine.render.Sprite;
import com.harmonygames.harmonyengine.render.Texture;
import com.harmonygames.harmonyengine.scene.Scene;

public class TestScene extends Scene {

    private GameObject gameObject;
    private final float playerSpeed = 200f;

    @Override
    public void onCreate() {

        mainCamera.transform.position.set(0, 0);

        gameObject = new GameObject("Example Object");
        gameObject.transform.scale.set(64, 64);
        gameObject.transform.position.set(100, 100);

        SpriteRenderer renderer = new SpriteRenderer();
        gameObject.addComponent(renderer);
        Sprite sprite = new Sprite();
        Texture texture = new Texture("/Users/nick227889/Dev/HarmonyEngine/src/main/resources/grass.jpg", gameObject.transform.scale);
        texture.initialize();
        sprite.setTexture(texture);
        renderer.setSprite(sprite);

        super.addGameObject(gameObject);
        super.onCreate();
    }

    @Override
    public void update(float deltaTime) {
        super.update(deltaTime);
    }

}