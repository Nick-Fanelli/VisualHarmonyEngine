package com.harmonygames.harmonyengine.render;

import com.harmonygames.harmonyengine.Log;
import com.harmonygames.harmonyengine.math.Scale;
import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL15;
import org.lwjgl.stb.STBImage;

import java.nio.ByteBuffer;
import java.nio.IntBuffer;

public class Texture {

    public static final int MIN_FILTER = GL15.GL_LINEAR;
    public static final int MAG_FILTER = GL15.GL_LINEAR;

    private String filepath;
    private int textureID;
    private int width, height;

    public Texture() {
        this.textureID = -1;
        this.width = -1;
        this.height = -1;
    }

    public Texture(String filepath, Scale scale) {
        this.filepath = filepath;

        // Generate texture on GPU
        this.textureID = GL15.glGenTextures();
        GL15.glBindTexture(GL15.GL_TEXTURE_2D, textureID);

        GL15.glTexParameteri(GL15.GL_TEXTURE_2D, GL15.GL_TEXTURE_MIN_FILTER, MIN_FILTER);
        GL15.glTexParameteri(GL15.GL_TEXTURE_2D, GL15.GL_TEXTURE_MAG_FILTER, MAG_FILTER);

        GL15.glTexImage2D(GL15.GL_TEXTURE_2D, 0, GL15.GL_RGB, width, height,
                0, GL15.GL_RGB, GL15.GL_UNSIGNED_BYTE, 0);
    }

    public void initialize() {
        // Generate Texture on GPU
        this.textureID = GL15.glGenTextures();
        GL15.glBindTexture(GL15.GL_TEXTURE_2D, textureID);

        GL15.glTexParameteri(GL15.GL_TEXTURE_2D, GL15.GL_TEXTURE_WRAP_S, GL15.GL_REPEAT);
        GL15.glTexParameteri(GL15.GL_TEXTURE_2D, GL15.GL_TEXTURE_WRAP_T, GL15.GL_REPEAT);

        GL15.glTexParameteri(GL15.GL_TEXTURE_2D, GL15.GL_TEXTURE_MIN_FILTER, MIN_FILTER);
        GL15.glTexParameteri(GL15.GL_TEXTURE_2D, GL15.GL_TEXTURE_MAG_FILTER, MAG_FILTER);

        IntBuffer width = BufferUtils.createIntBuffer(1);
        IntBuffer height = BufferUtils.createIntBuffer(1);
        IntBuffer channels = BufferUtils.createIntBuffer(1);

        STBImage.stbi_set_flip_vertically_on_load(true);

        ByteBuffer image = STBImage.stbi_load(filepath, width, height, channels, 0);

        if(image != null) {
            this.width = width.get(0);
            this.height = height.get(0);

            if(channels.get(0) == 3) { // RGB
                GL15.glTexImage2D(GL15.GL_TEXTURE_2D, 0, GL15.GL_RGB, width.get(0), height.get(0),
                        0, GL15.GL_RGB, GL15.GL_UNSIGNED_BYTE, image);
            } else if(channels.get(0) == 4) { // RGBA
                GL15.glTexImage2D(GL15.GL_TEXTURE_2D, 0, GL15.GL_RGBA, width.get(0), height.get(0),
                        0, GL15.GL_RGBA, GL15.GL_UNSIGNED_BYTE, image);
            } else {
                Log.fatalError("Unknown number of image channels '" + channels.get(0) + "' in image '" + filepath + "'");
            }

            STBImage.stbi_image_free(image);
        }
    }

    public void bind() {
        if(textureID == -1) Log.warn("Texture ID of image '" + filepath + "' holds a textureID pointer of -1!\n" +
                "\tThis may result in the texture not binding or an OpenGL error!!\n" +
                "\tThe textureID pointer should hold the memory location of the texture!");
        GL15.glBindTexture(GL15.GL_TEXTURE_2D, textureID);
    }

    public void unbind() {
        GL15.glBindTexture(GL15.GL_TEXTURE_2D, 0);
    }

    public int getTextureID() { return this.textureID; }
    public String getFilepath() { return this.filepath; }

    public int getWidth() { return this.width; }
    public int getHeight() { return this.height; }

    @Override
    public boolean equals(Object object) {
        if(!(object instanceof Texture)) return false;
        Texture texture = (Texture) object;
        return texture.getWidth() == this.width && texture.getHeight() == this.height && texture.getTextureID() == this.textureID
                && texture.getFilepath().equals(this.filepath);
    }
}
