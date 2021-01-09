package com.harmonygames.harmonyengine.mesh;

import org.joml.Vector4f;
import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL15;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL30;

import java.nio.ByteBuffer;
import java.nio.FloatBuffer;

public class Mesh {

    private final int vaoID;
    private final int eabID;

    public Mesh(float[] vertices, float[] colors, byte[] indices) {

        FloatBuffer verticesBuffer = BufferUtils.createFloatBuffer(vertices.length);
        verticesBuffer.put(vertices);
        verticesBuffer.flip();

        FloatBuffer colorsBuffer = BufferUtils.createFloatBuffer(vertices.length);
        colorsBuffer.put(colors);
        colorsBuffer.flip();

        ByteBuffer indicesBuffer = BufferUtils.createByteBuffer(indices.length);
        indicesBuffer.put(indices);
        indicesBuffer.flip();

        // Bind the vao
        vaoID = GL30.glGenVertexArrays();
        GL30.glBindVertexArray(vaoID);


        // Bind the vertices
        int vboID = GL15.glGenBuffers();
        GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, vboID);
        GL15.glBufferData(GL15.GL_ARRAY_BUFFER, verticesBuffer, GL15.GL_STATIC_DRAW);
        GL20.glVertexAttribPointer(0, 3, GL11.GL_FLOAT, false, 0, 0);
        GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, 0);

        int vboColorID = GL15.glGenBuffers();
        GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, vboColorID);
        GL15.glBufferData(GL15.GL_ARRAY_BUFFER, colorsBuffer, GL15.GL_STATIC_DRAW);
        GL20.glVertexAttribPointer(1, 4, GL11.GL_FLOAT, false, 0, 0);

        // Deselect (bind to 0) the VAO
        GL30.glBindVertexArray(0);

        // Bind the indices
        eabID = GL15.glGenBuffers();
        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, eabID);
        GL15.glBufferData(GL15.GL_ELEMENT_ARRAY_BUFFER, indicesBuffer, GL15.GL_STATIC_DRAW);

        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, 0);

        // TODO: SETUP THE INT BUFFER FOR THE INDICIES
    }

    public int getVaoID() { return this.vaoID; }
    public int getEabID() { return this.eabID; }

}
