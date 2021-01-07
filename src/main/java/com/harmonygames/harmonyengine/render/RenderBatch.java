package com.harmonygames.harmonyengine.render;

import com.harmonygames.harmonyengine.Log;
import com.harmonygames.harmonyengine.objects.compoonents.Renderer;
import com.harmonygames.harmonyengine.scene.SceneManager;
import com.harmonygames.harmonyengine.utils.Assets;
import org.joml.Vector2f;
import org.joml.Vector4f;
import org.lwjgl.opengl.GL30;

import java.util.ArrayList;

public class RenderBatch {

    private final int POSITION_SIZE = 2; // Two floats
    private final int COLOR_SIZE = 4; // Four floats r, g, b, a
    private final int TEXTURE_COORDS_SIZE = 2; // Two floats
    private final int TEXTURE_ID_SIZE = 1; // One float

    private final int POSITION_OFFSET = 0;
    private final int COLOR_OFFSET = POSITION_OFFSET + POSITION_SIZE * Float.BYTES;
    private final int TEXTURE_COORDS_OFFSET = COLOR_OFFSET + COLOR_SIZE * Float.BYTES;
    private final int TEXTURE_ID_OFFSET = TEXTURE_COORDS_OFFSET + TEXTURE_COORDS_SIZE * Float.BYTES;
    private final int VERTEX_SIZE = 9;
    private final int VERTEX_SIZE_BYTES = VERTEX_SIZE * Float.BYTES;

    private Renderer[] renderers;
    private int numRenderers;
    private boolean hasRoom;
    private float[] vertices;
    private int[] textureSlots = { 0, 1, 2, 3, 4, 5, 6, 7 };

    private ArrayList<Texture> textures;
    private int vaoID, vboID;
    private int maxBatchSize;
    private Shader shader;
    private int zIndex;

    public RenderBatch(int maxBatchSize, int zIndex) {
        this.shader = Assets.getShader("assets/shaders/default");
        this.renderers = new Renderer[maxBatchSize];
        this.maxBatchSize = maxBatchSize;
        this.zIndex = zIndex;

        // Setup four vertices per quad
        vertices = new float[maxBatchSize * 4 * VERTEX_SIZE];

        this.numRenderers = 0;
        this.hasRoom = true;
        this.textures = new ArrayList<>();
    }

    public void render() {
        boolean rebufferData = false;

        for(int i = 0; i < numRenderers; i++) {
            Renderer renderer = renderers[i];

            if(renderer.shouldRedraw()) {
                this.loadVertexProperties(i);
                renderer.setDrawn();
                rebufferData = true;
            }
        }

        if(rebufferData) {
            GL30.glBindBuffer(GL30.GL_ARRAY_BUFFER, vboID);
            GL30.glBufferSubData(GL30.GL_ARRAY_BUFFER, 0, vertices);
        }

        // Attach Shader
        shader.bind();
        shader.uploadMat4f("uProjection", SceneManager.getActiveScene().getMainCamera().getProjectionMatrix());
        shader.uploadMat4f("uView", SceneManager.getActiveScene().getMainCamera().getViewMatrix());

        // Upload and setup the texture stuff to GLSL
        for(int i = 0; i < textures.size(); i++) {
            GL30.glActiveTexture(GL30.GL_TEXTURE0 + i + 1);
            textures.get(i).bind();
        }

        shader.uploadIntArray("uTextures", textureSlots);

        GL30.glBindVertexArray(vaoID);
        GL30.glEnableVertexAttribArray(0);
        GL30.glEnableVertexAttribArray(1);

        GL30.glDrawElements(GL30.GL_TRIANGLES, this.numRenderers * 6, GL30.GL_UNSIGNED_INT, 0);

        GL30.glDisableVertexAttribArray(0);
        GL30.glDisableVertexAttribArray(1);
        GL30.glBindVertexArray(0);

        for(int i = 0; i < textures.size(); i++) {
            GL30.glActiveTexture(GL30.GL_TEXTURE0 + i + 1);
            textures.get(i).unbind();
        }

        shader.unbind();
    }

    private void loadVertexProperties(int index) {
        Renderer renderer = this.renderers[index];

        // Find offset within array
        int offset = index * 4 * VERTEX_SIZE;

        Vector4f color = renderer.getColor();
        Vector2f[] textureCoords = renderer.getTextureCoords();

        int textureID = 0;
        if(renderer.getTexture() != null) {
            for(int i = 0; i < textures.size(); i++) {
                if(textures.get(i) == renderer.getTexture()) {
                    textureID = i + 1;
                    break;
                }
            }
        }

        // Add the vertices with the appropriate properties
        float xAdd = 1.0f;
        float yAdd = 1.0f;

        for(int i = 0; i < 4; i++) {
            if(i == 1) yAdd = 0.0f;
            else if(i == 2) xAdd = 0.0f;
            else if(i == 3) yAdd = 1.0f;

            // Load the position
            vertices[offset] = renderer.getGameObject().transform.position.x + (xAdd * renderer.getGameObject().transform.scale.width);
            vertices[offset + 1] = renderer.getGameObject().transform.position.y + (yAdd * renderer.getGameObject().transform.scale.height);

            // Load the color data
            vertices[offset + 2] = color.x;
            vertices[offset + 3] = color.y;
            vertices[offset + 4] = color.z;
            vertices[offset + 5] = color.w;

            // Load the texture coordinates
            vertices[offset + 6] = textureCoords[i].x;
            vertices[offset + 7] = textureCoords[i].y;

            // Load texture ids
            vertices[offset + 8] = textureID;

            offset += VERTEX_SIZE;
        }
    }

    public void addRenderer(Renderer renderer) {
        // Get index and add render object
        int index = this.numRenderers;
        if(index > maxBatchSize) {
            Log.error("Should not be accessing an index greater than the max batch size in the render batch!");
        }

        this.renderers[index] = renderer;
        this.numRenderers++;

        if(renderer.getTexture() != null) {
            if(!textures.contains(renderer.getTexture())) {
                this.textures.add(renderer.getTexture());
            }
        }

        // Add the properties to the local vertices array
        this.loadVertexProperties(index);

        if(numRenderers >= this.maxBatchSize) {
            this.hasRoom = false;
        }
    }

    public void start() {
        // Generate and bind a vertex array object
        vaoID = GL30.glGenVertexArrays();
        GL30.glBindVertexArray(vaoID);

        // Allocate space for vertices
        vboID = GL30.glGenBuffers();
        GL30.glBindBuffer(GL30.GL_ARRAY_BUFFER, vboID);
        GL30.glBufferData(GL30.GL_ARRAY_BUFFER, (long) vertices.length * Float.BYTES, GL30.GL_DYNAMIC_DRAW);

        // Create and push indices buffer
        int eboID = GL30.glGenBuffers();
        int[] indices = generateIndices();
        GL30.glBindBuffer(GL30.GL_ELEMENT_ARRAY_BUFFER, eboID);
        GL30.glBufferData(GL30.GL_ELEMENT_ARRAY_BUFFER, indices, GL30.GL_STATIC_DRAW);

        // Enable the buffer and attribute pointers
        GL30.glVertexAttribPointer(0, POSITION_SIZE, GL30.GL_FLOAT, false, VERTEX_SIZE_BYTES, POSITION_OFFSET);
        GL30.glEnableVertexAttribArray(0);

        GL30.glVertexAttribPointer(1, COLOR_SIZE, GL30.GL_FLOAT, false, VERTEX_SIZE_BYTES, COLOR_OFFSET);
        GL30.glEnableVertexAttribArray(1);

        GL30.glVertexAttribPointer(2, TEXTURE_COORDS_SIZE, GL30.GL_FLOAT, false, VERTEX_SIZE_BYTES, TEXTURE_COORDS_OFFSET);
        GL30.glEnableVertexAttribArray(2);

        GL30.glVertexAttribPointer(3, TEXTURE_ID_SIZE, GL30.GL_FLOAT, false, VERTEX_SIZE_BYTES, TEXTURE_ID_OFFSET);
        GL30.glEnableVertexAttribArray(3);
    }

    private int[] generateIndices() {
        // 6 indices per quad (3 per triangle)
        int[] elements = new int[6 * maxBatchSize];

        for(int i = 0; i < maxBatchSize; i++) {
            this.loadElementIndices(elements, i);
        }

        return elements;
    }

    private void loadElementIndices(int[] elements, int index) {
        int offsetArrayIndex = 6 * index;
        int offset = 4 * index;

        // Triangle 1
        elements[offsetArrayIndex] = offset + 3;
        elements[offsetArrayIndex + 1] = offset + 2;
        elements[offsetArrayIndex + 2] = offset;

        // Triangle 2
        elements[offsetArrayIndex + 3] = offset;
        elements[offsetArrayIndex + 4] = offset + 2;
        elements[offsetArrayIndex + 5] = offset + 1;
    }

    public boolean hasRoom() { return this.hasRoom; }
    public boolean hasTextureRoom() { return this.textures.size() < 8; }
    public boolean hasTexture(Texture texture) { return this.textures.contains(texture); }
    public int getzIndex() { return this.zIndex; }

}
