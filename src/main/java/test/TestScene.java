package test;

import com.harmonygames.harmonyengine.mesh.Mesh2D;
import com.harmonygames.harmonyengine.object.Camera;
import com.harmonygames.harmonyengine.render.Shader;
import com.harmonygames.harmonyengine.scene.Scene;
import com.harmonygames.harmonyengine.utils.Assets;
import org.joml.Vector4f;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL15;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL30;

public class TestScene extends Scene {

    private Mesh2D mesh2D;
    private Shader shader;
    private Camera camera;

    float[] vertices = {
            -0.8f, 0.5f,    // Left top         ID: 0
            -0.8f, -0.5f,    // Left bottom      ID: 1
            -0.25f, -0.5f,     // Right bottom     ID: 2
            -0.25f, 0.5f,     // Right left       ID: 3

            0.8f, 0.5f,
            0.8f, -0.5f,
            0.25f, -0.5f,
            0.25f, 0.5f
    };

    Vector4f color = new Vector4f(1, 0, 0, 1);

    int[] indices = {
            // Left bottom triangle
            0, 1, 2,
            // Right top triangle
            2, 3, 0,

            4, 5, 6,
            6, 7, 4
    };

    @Override
    public void onCreate() {
        super.onCreate();

        camera = new Camera("Main Camera");

        mesh2D = new Mesh2D(vertices, indices);
        shader = Assets.loadShader("/shaders/default.glsl");

        System.out.println(Byte.MAX_VALUE);
        System.out.println(Integer.MAX_VALUE);
    }

    @Override
    public void update(float deltaTime) {
        super.update(deltaTime);

        shader.bind();

        GL30.glBindVertexArray(mesh2D.getVaoID());
        GL20.glEnableVertexAttribArray(0);

        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, mesh2D.getEabID());

        GL11.glDrawElements(GL11.GL_TRIANGLES, indices.length, GL11.GL_UNSIGNED_INT, 0);

        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, 0);

        GL20.glDisableVertexAttribArray(0);
        GL30.glBindVertexArray(0);

        shader.unbind();
    }

}