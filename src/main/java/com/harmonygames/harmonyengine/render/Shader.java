package com.harmonygames.harmonyengine.render;

import com.harmonygames.harmonyengine.Log;
import com.harmonygames.harmonyengine.utils.FileUtils;
import org.joml.Matrix4f;
import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL20;

import java.io.File;
import java.nio.FloatBuffer;
import java.util.Locale;

public class Shader {

    private final int programID;

    public enum ShaderType {
        Vertex(GL20.GL_VERTEX_SHADER),
        Fragment(GL20.GL_FRAGMENT_SHADER);

        public final int glShaderType;

        ShaderType(int glShaderType) {
            this.glShaderType = glShaderType;
        }

        public static String getAsStringArray() {
            StringBuilder builder = new StringBuilder("{ ");

            for(int i = 0; i < ShaderType.values().length; i++) {
                builder.append(ShaderType.values()[i].name().toLowerCase(Locale.ROOT));
                if(i < ShaderType.values().length - 1) builder.append(", ");
            }

            builder.append(" }");
            return builder.toString();
        }
    }

    public Shader(String shaderName, String shaderData) {
        this.programID = GL20.glCreateProgram();

        String[] shaderFiles = shaderData.split("#type");

        for(String string : shaderFiles) {
            string = string.trim();
            if(string.startsWith("//") || string.isBlank()) continue;

            boolean hasBeenAttached = false;

            for(ShaderType type : ShaderType.values()) {
                if(string.startsWith(type.name().toLowerCase(Locale.ROOT))) {
                    attachShader(string.replaceFirst(type.name().toLowerCase(Locale.ROOT), ""), type.glShaderType);
                    hasBeenAttached = true;
                    break;
                }
            }

            if(!hasBeenAttached) {
                Log.error("Couldn't identify shader type: '" + string.split("\n")[0] + "' in shader '" + shaderName + "'\n" +
                        "\tThe valid shader types are: " + ShaderType.getAsStringArray() + "\n" +
                        "\tEg. '#type vertex' then followed by the vertex code\n" +
                        "\tAfter the vertex code write '#type fragment' followed by the fragment code etc.");
            }

        }

        this.link();
    }

    public void attachShader(String shaderSource, int shaderType) {
        int shaderID = GL20.glCreateShader(shaderType);
        GL20.glShaderSource(shaderID, shaderSource);

        GL20.glCompileShader(shaderID);

        if(GL20.glGetShaderi(shaderID, GL20.GL_COMPILE_STATUS) == GL20.GL_FALSE) {
            Log.error("Error creating vertex shader!");
            Log.fatalError("\t" + GL20.glGetShaderInfoLog(shaderID, GL20.glGetShaderi(shaderID, GL20.GL_INFO_LOG_LENGTH)));
        }

        GL20.glAttachShader(programID, shaderID);

//        return shaderID;
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

        GL20.glDeleteProgram(programID);
    }

    public void addUniformMatrix4f(String varName, Matrix4f matrix4f) {
        int uniformLocation = GL20.glGetUniformLocation(programID, varName);
        this.bind();
        FloatBuffer matrixBuffer = BufferUtils.createFloatBuffer(16);
        matrix4f.get(matrixBuffer);
        GL20.glUniformMatrix4fv(uniformLocation, false, matrixBuffer);
    }

    public void addUniformIntArray(String varName, int[] array) {
        int varLocation = GL20.glGetUniformLocation(programID, varName);
        this.bind();
        GL20.glUniform1iv(varLocation, array);
    }
}
