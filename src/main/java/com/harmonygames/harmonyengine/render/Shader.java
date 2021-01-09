package com.harmonygames.harmonyengine.render;

import com.harmonygames.harmonyengine.utils.FileUtils;
import org.joml.Matrix4f;
import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL20;

import java.nio.FloatBuffer;

public class Shader {

    private int programID, vertexID, fragmentID;

    public Shader() {
        this.programID = GL20.glCreateProgram();
        this.attachVertexShader("vertex.glsl");
        this.attachFragmentShader("fragment.glsl");
        this.link();
    }

    public void attachVertexShader(String name) {
        String vertexShaderSource = FileUtils.readFromFile(name);

        vertexID = GL20.glCreateShader(GL20.GL_VERTEX_SHADER);
        GL20.glShaderSource(vertexID, vertexShaderSource);

        GL20.glCompileShader(vertexID);

        if(GL20.glGetShaderi(vertexID, GL20.GL_COMPILE_STATUS) == GL20.GL_FALSE) {
            throw new RuntimeException("Error creating vertex shader\n"
                    + GL20.glGetShaderInfoLog(vertexID, GL20.glGetShaderi(vertexID, GL20.GL_INFO_LOG_LENGTH)));
        }

        GL20.glAttachShader(programID, vertexID);
    }

    public void attachFragmentShader(String name) {
        String fragmentShaderSource = FileUtils.readFromFile(name);

        fragmentID = GL20.glCreateShader(GL20.GL_FRAGMENT_SHADER);
        GL20.glShaderSource(fragmentID, fragmentShaderSource);

        GL20.glCompileShader(fragmentID);

        if(GL20.glGetShaderi(fragmentID, GL20.GL_COMPILE_STATUS) == GL20.GL_FALSE) {
            throw new RuntimeException("Error creating vertex shader\n"
                    + GL20.glGetShaderInfoLog(fragmentID, GL20.glGetShaderi(fragmentID, GL20.GL_INFO_LOG_LENGTH)));
        }

        GL20.glAttachShader(programID, fragmentID);
    }

    public void link() {
        GL20.glLinkProgram(programID);

        if(GL20.glGetProgrami(programID, GL20.GL_LINK_STATUS) == GL20.GL_FALSE) {
            throw new RuntimeException("Unable to link shader program!"
                    + GL20.glGetProgramInfoLog(programID, GL20.glGetProgrami(programID, GL20.GL_INFO_LOG_LENGTH)));
        }
    }

    public void bind() {
        GL20.glUseProgram(programID);
    }

    public void unbind() {
        GL20.glUseProgram(0);
    }

    public void dispose() {
        GL20.glUseProgram(0);

        GL20.glDetachShader(programID, vertexID);
        GL20.glDetachShader(programID, fragmentID);

        GL20.glDeleteShader(vertexID);
        GL20.glDeleteShader(fragmentID);

        GL20.glDeleteProgram(programID);
    }

    public void addUniformMatrix4f(String varName, Matrix4f matrix4f) {
        int uniformLocation = GL20.glGetUniformLocation(programID, varName);
        this.bind();
        FloatBuffer matrixBuffer = BufferUtils.createFloatBuffer(16);
        matrix4f.get(matrixBuffer);
        GL20.glUniformMatrix4fv(uniformLocation, false, matrixBuffer);
    }
}
