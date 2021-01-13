package test;

import com.harmonygames.harmonyengine.object.GameObject;
import com.harmonygames.harmonyengine.object.component.SpriteRenderer;
import com.harmonygames.harmonyengine.render.Sprite;
import com.harmonygames.harmonyengine.scene.Scene;

public class TestScene extends Scene {

    @Override
    public void onCreate() {

        mainCamera.transform.position.set(0, 0);

        GameObject gameObject = new GameObject("Example Object");
        gameObject.transform.scale.set(32, 32);
        gameObject.transform.position.set(100, 100);

        SpriteRenderer renderer = new SpriteRenderer();
        gameObject.addComponent(renderer);
        renderer.setSprite(new Sprite());

        super.addGameObject(gameObject);

        super.onCreate();
    }

    @Override
    public void update(float deltaTime) {
        super.update(deltaTime);
    }

}