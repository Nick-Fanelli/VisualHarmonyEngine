package com.harmonygames.harmonyengine.mesh;

public class Mesh {

    private int vaoID;
    private int vertexCount;

    public Mesh(int vaoID, int vertexCount) {
        this.vaoID = vaoID;
        this.vertexCount = vertexCount;
    }

    public int getVaoID() { return this.vaoID; }
    public int getVertexCount() { return this.vertexCount; }

}
