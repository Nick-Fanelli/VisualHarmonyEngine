package test;

import com.harmonygames.harmonyengine.mesh.Mesh;
import com.harmonygames.harmonyengine.render.Shader;
import com.harmonygames.harmonyengine.scene.Scene;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL15;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL30;

public class TestScene extends Scene {

    private Mesh mesh;
    private Shader shader;

    float[] vertices = {
            -0.5f, 0.5f, 0f,    // Left top         ID: 0
            -0.5f, -0.5f, 0f,   // Left bottom      ID: 1
            0.5f, -0.5f, 0f,    // Right bottom     ID: 2
            0.5f, 0.5f, 0f      // Right left       ID: 3
    };

    float[] colors = new float[]
            {
                    1, 0, 0, 1,  // Red color, for the first vertex
                    0, 1, 0, 1,  // Green color, for the second vertex
                    0, 0, 1, 1,   // Blue color, for the third vertex
            };

    byte[] indices = {
            // Left bottom triangle
            0, 1, 2,
            // Right top triangle
            2, 3, 0
    };

    @Override
    public void onCreate() {
        super.onCreate();

        mesh = new Mesh(vertices, colors, indices);
        shader = new Shader();
    }

    @Override
    public void update(float deltaTime) {
        super.update(deltaTime);

        shader.bind();

        GL30.glBindVertexArray(mesh.getVaoID());
        GL20.glEnableVertexAttribArray(0);
        GL20.glEnableVertexAttribArray(1);

        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, mesh.getEabID());

        GL11.glDrawElements(GL11.GL_TRIANGLES, indices.length, GL11.GL_UNSIGNED_BYTE, 0);

        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, 0);

        GL20.glDisableVertexAttribArray(0);
        GL20.glDisableVertexAttribArray(1);
        GL30.glBindVertexArray(0);

        shader.unbind();
    }

}