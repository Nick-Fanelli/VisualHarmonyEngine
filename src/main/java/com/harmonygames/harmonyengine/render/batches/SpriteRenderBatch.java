package com.harmonygames.harmonyengine.render.batches;

import com.harmonygames.harmonyengine.Log;
import com.harmonygames.harmonyengine.object.component.SpriteRenderer;
import com.harmonygames.harmonyengine.render.Shader;
import com.harmonygames.harmonyengine.render.Sprite;
import com.harmonygames.harmonyengine.render.Texture;
import com.harmonygames.harmonyengine.scene.Scene;
import com.harmonygames.harmonyengine.utils.Assets;
import org.joml.Vector2f;
import org.joml.Vector4f;
import org.lwjgl.opengl.GL15;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL30;

import java.util.ArrayList;

public class SpriteRenderBatch extends RenderBatch<SpriteRenderer>  {

    public static final Shader shader = Assets.loadShader("/shaders/sprite.glsl");

    public static final int POSITION_SIZE = 2; // Two floats x and y
    public static final int COLOR_SIZE = 4; // Four floats r, g, b, a
    public static final int TEXTURE_COORDS_SIZE = 2; // Two floats x and y
    public static final int TEXTURE_ID_SIZE = 1; // One float: position

    public static final int POSITION_OFFSET = 0; // Store first
    public static final int COLOR_OFFSET = POSITION_OFFSET + POSITION_SIZE * Float.BYTES; // Store second
    public static final int TEXTURE_COORDS_OFFSET = COLOR_OFFSET + COLOR_SIZE * Float.BYTES; // Store third
    public static final int TEXTURE_ID_OFFSET = TEXTURE_COORDS_OFFSET + TEXTURE_COORDS_SIZE * Float.BYTES; // Store fourth
    public static final int VERTEX_SIZE = 9;
    public static final int VERTEX_SIZE_BYTES = VERTEX_SIZE * Float.BYTES;

    private SpriteRenderer[] spriteRenderers;

    private final float[] vertices;
    private final int[] textureSlots = { 0, 1, 2, 3, 4, 5, 6, 7 };

    private final ArrayList<Texture> textures;
    private int vaoID, vboID;

    public SpriteRenderBatch(Scene scene, int zIndex) {
        super(scene, zIndex);

        this.spriteRenderers = new SpriteRenderer[RENDER_BATCH_CAPACITY];
        this.vertices = new float[RENDER_BATCH_CAPACITY * 4 * VERTEX_SIZE]; // 4 vertices per quad
        this.textures = new ArrayList<>();
    }

    @Override
    public void onCreate() {
        // Create and bind the vertex array object
        vaoID = GL30.glGenVertexArrays();
        GL30.glBindVertexArray(vaoID);

        // Allocate space for the vertices
        vboID = GL15.glGenBuffers();
        GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, vboID);
        GL15.glBufferData(GL15.GL_ARRAY_BUFFER, (long) vertices.length * Float.BYTES, GL15.GL_DYNAMIC_DRAW);

        // Create and upload indices buffer
        int eboID = GL15.glGenBuffers();
        int[] indices = generateIndices();
        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, eboID);
        GL15.glBufferData(GL15.GL_ELEMENT_ARRAY_BUFFER, indices, GL15.GL_STATIC_DRAW);

        // Enable the buffer attribute pointers
        GL20.glVertexAttribPointer(0, POSITION_SIZE, GL15.GL_FLOAT, false, VERTEX_SIZE_BYTES, POSITION_OFFSET);
        GL20.glEnableVertexAttribArray(0);

        GL20.glVertexAttribPointer(1, COLOR_SIZE, GL15.GL_FLOAT, false, VERTEX_SIZE_BYTES, COLOR_OFFSET);
        GL20.glEnableVertexAttribArray(1);

        GL20.glVertexAttribPointer(2, TEXTURE_COORDS_SIZE, GL15.GL_FLOAT, false, VERTEX_SIZE_BYTES, TEXTURE_COORDS_OFFSET);
        GL20.glEnableVertexAttribArray(2);

        GL20.glVertexAttribPointer(3, TEXTURE_ID_SIZE, GL15.GL_FLOAT, false, VERTEX_SIZE_BYTES, TEXTURE_ID_OFFSET);
        GL20.glEnableVertexAttribArray(3);
    }

    @Override
    public void addRenderComponent(SpriteRenderer component) {
        int index = this.size;
        this.spriteRenderers[size] = component;
        this.size++;

        if(component.getTexture() != null) {
            if(!textures.contains(component.getTexture())) {
                textures.add(component.getTexture());
            }
        }

        this.loadVertexProperties(index);
    }

    @Override
    public void render() {
        boolean shouldRebufferData = false;

        for(int i = 0; i < size; i++) {
            SpriteRenderer spriteRenderer = spriteRenderers[i];
            if(spriteRenderer.shouldRedraw()) {
                this.loadVertexProperties(i);
                spriteRenderer.setDrawn();
                shouldRebufferData = true;
            }
        }

        if (shouldRebufferData) {
            GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, vboID);
            GL15.glBufferSubData(GL15.GL_ARRAY_BUFFER, 0, vertices);
        }

        // Bind Shader and Uniform Data
        shader.bind();
        shader.addUniformMatrix4f("uProjection", super.scene.getMainCamera().getProjectionMatrix());
        shader.addUniformMatrix4f("uView", super.scene.getMainCamera().getViewMatrix());

        // Upload and setup texture to GLSL
        for(int i = 0; i < textures.size(); i++) {
            GL15.glActiveTexture(GL15.GL_TEXTURE0 + i + 1); // the 1 offsets because texture 0 will be no texture!
            textures.get(i).bind();
        }

        shader.addUniformIntArray("uTextures", textureSlots);

        GL30.glBindVertexArray(vaoID);
        GL30.glEnableVertexAttribArray(0);
        GL30.glEnableVertexAttribArray(1);

        GL15.glDrawElements(GL15.GL_TRIANGLES, super.size * VERTEX_SIZE, GL15.GL_UNSIGNED_INT, 0);

        GL30.glDisableVertexAttribArray(0);
        GL30.glDisableVertexAttribArray(1);
        GL30.glBindVertexArray(0);


        for(int i = 0; i < textures.size(); i++) {
            GL15.glActiveTexture(GL15.GL_TEXTURE0 + i + 1); // the 1 offsets because texture 0 will be no texture!
            textures.get(i).unbind();
        }

        shader.unbind();
    }

    @Override
    public void removeRenderComponent(SpriteRenderer component) {

    }

    @Override
    public void onDestroy() {
        GL15.glDeleteBuffers(vboID);
        GL30.glDeleteVertexArrays(vaoID);
    }

    // ====================================================================================
    // Generation Methods for Creating a Quad's Indices
    // ====================================================================================

    private void loadVertexProperties(int index) {
        SpriteRenderer sprite = this.spriteRenderers[index];

        // Find offset within array (4 vertices per sprite)
        int offset = index * 4 * VERTEX_SIZE;

        Vector4f color = sprite.getColor();
        Vector2f[] texCoords = sprite.getTextureCoords();

        int texID = 0;
        if(sprite.getTexture() != null) {
            for(int i = 0; i < textures.size(); i++) {
                if(textures.get(i) == sprite.getTexture()) {
                    texID = i + 1;
                    break;
                }
            }
        }

        // Add vertices with the appropriate properties
        float xAdd = 1.0f;
        float yAdd = 1.0f;
        for (int i=0; i < 4; i++) {
            if (i == 1) {
                yAdd = 0.0f;
            } else if (i == 2) {
                xAdd = 0.0f;
            } else if (i == 3) {
                yAdd = 1.0f;
            }

            // Load position
            vertices[offset] = sprite.getGameObject().transform.position.x + (xAdd * sprite.getGameObject().transform.scale.width);
            vertices[offset + 1] = sprite.getGameObject().transform.position.y + (yAdd * sprite.getGameObject().transform.scale.height);

            // Load color
            vertices[offset + 2] = color.x;
            vertices[offset + 3] = color.y;
            vertices[offset + 4] = color.z;
            vertices[offset + 5] = color.w;

            // Load texture coordinates
            vertices[offset + 6] = texCoords[i].x;
            vertices[offset + 7] = texCoords[i].y;

            // Load texture ids
            vertices[offset + 8] = texID;

            offset += VERTEX_SIZE;
        }
    }

    private int[] generateIndices() {
        // 6 indices per quad (3 per triangle)
        int[] elements = new int[6 * RENDER_BATCH_CAPACITY];
        for (int i=0; i < RENDER_BATCH_CAPACITY; i++) {
            loadElementIndices(elements, i);
        }

        return elements;
    }

    private void loadElementIndices(int[] elements, int index) {
        int offsetArrayIndex = 6 * index;
        int offset = 4 * index;

        // 3, 2, 0, 0, 2, 1        7, 6, 4, 4, 6, 5
        // Triangle 1
        elements[offsetArrayIndex] = offset + 3;
        elements[offsetArrayIndex + 1] = offset + 2;
        elements[offsetArrayIndex + 2] = offset;

        // Triangle 2
        elements[offsetArrayIndex + 3] = offset;
        elements[offsetArrayIndex + 4] = offset + 2;
        elements[offsetArrayIndex + 5] = offset + 1;
    }
}
