package com.harmonygames.harmonyengine.render;

import com.harmonygames.harmonyengine.Log;
import com.harmonygames.harmonyengine.utils.FileUtils;
import org.joml.Matrix4f;
import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL20;

import java.io.File;
import java.nio.FloatBuffer;

public class Shader {

    private final int programID;
    private int fragmentID = 0, vertexID = 0;

    public Shader(File[] shaderFiles) {
        this.programID = GL20.glCreateProgram();

        for(File file : shaderFiles) {
            String[] splits = file.getAbsolutePath().split("\\.");
            if(splits.length >= 3) {
                String type = splits[splits.length - 2];

                // TODO: Handle geometry shaders
                if(type.equalsIgnoreCase("vert")) vertexID = this.attachShader(file, GL20.GL_VERTEX_SHADER);
                else if(type.equalsIgnoreCase("frag")) fragmentID = this.attachShader(file, GL20.GL_FRAGMENT_SHADER);
            } else {
                Log.warn("Shader, '" + file.getName() + "' does not follow the conventions of 'name.vert.glsl' or 'name.frag.glsl'");
            }
        }

        if(fragmentID == 0 && vertexID == 0) {
            Log.warn("Both the fragment and vertex shaders have not been created! This will most likely result in a failure to link the shader program!" +
                    "\n\tInstead make sure that you are referencing a directory that contains the correct shaders with the following conventions:" +
                    "\n\t'name.vert.glsl' and 'name.frag.glsl' - Note the name does not matter just the two extensions!!!" +
                    "\n\tThe extensions tell Harmony Engine which type of shader they are!!!");
        }

        this.link();
    }

    public int attachShader(File file, int shaderType) {
        String shaderSource = FileUtils.readFromFile(file);

        int shaderID = GL20.glCreateShader(shaderType);
        GL20.glShaderSource(shaderID, shaderSource);

        GL20.glCompileShader(shaderID);

        if(GL20.glGetShaderi(shaderID, GL20.GL_COMPILE_STATUS) == GL20.GL_FALSE) {
            Log.error("Error creating vertex shader!");
            Log.fatalError("\t" + GL20.glGetShaderInfoLog(shaderID, GL20.glGetShaderi(shaderID, GL20.GL_INFO_LOG_LENGTH)));
        }

        GL20.glAttachShader(programID, shaderID);

        return shaderID;
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

        if(vertexID != 0) GL20.glDetachShader(programID, vertexID);
        if(fragmentID != 0) GL20.glDetachShader(programID, fragmentID);

        if(vertexID != 0) GL20.glDeleteShader(vertexID);
        if(fragmentID != 0) GL20.glDeleteShader(fragmentID);

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
