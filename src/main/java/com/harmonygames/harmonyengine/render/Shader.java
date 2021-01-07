package com.harmonygames.harmonyengine.render;

import com.harmonygames.harmonyengine.Log;
import org.joml.Matrix4f;
import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL30;

import java.io.File;
import java.io.IOException;
import java.nio.FloatBuffer;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Shader {

    private int shaderProgramID;
    private boolean currentlyInUse = false;

    private final String shaderLocation;
    private final String vertexFilepath;
    private final String fragmentFilepath;

    private String vertexSource;
    private String fragmentSource;

    public Shader(File directoryLocation) {
        this.shaderLocation = directoryLocation.getAbsolutePath();

        this.vertexFilepath = directoryLocation.getAbsolutePath() + File.separator + directoryLocation.getName() + "Vertex.glsl";
        this.fragmentFilepath = directoryLocation.getAbsolutePath() + File.separator + directoryLocation.getName() + "Fragment.glsl";

        try {
            this.vertexSource = new String(Files.readAllBytes(Paths.get(vertexFilepath)));
            this.fragmentSource = new String(Files.readAllBytes(Paths.get(fragmentFilepath)));
        } catch (IOException e) {
            Log.error("Could not load the vertex and fragment sources");
            e.printStackTrace();
        }
    }

    public void compile() {
        // ====================================================
        // Compile and Link Shaders
        // ====================================================
        int vertexID, fragmentID;

        // Load and compile vertex shader
        vertexID = GL20.glCreateShader(GL20.GL_VERTEX_SHADER);
        // Pass the shader source to the GPU
        GL20.glShaderSource(vertexID, vertexSource);
        GL20.glCompileShader(vertexID);

        // Check for errors in the compilation
        int compileStatus = GL20.glGetShaderi(vertexID, GL20.GL_COMPILE_STATUS);
        if(compileStatus == GL20.GL_FALSE) {
            int length = GL20.glGetShaderi(vertexID, GL20.GL_INFO_LOG_LENGTH);
            Log.error(vertexFilepath + ":\n\tVertex shader compilation failed!");
            Log.error(GL20.glGetShaderInfoLog(vertexID, length));
            System.exit(-1);
        }

        // Load and compile the fragment shader
        fragmentID = GL20.glCreateShader(GL20.GL_FRAGMENT_SHADER);
        // Pass the shader source into the GPU
        GL20.glShaderSource(fragmentID, fragmentSource);
        GL20.glCompileShader(fragmentID);

        // Check for errors in the compilation
        compileStatus = GL20.glGetShaderi(fragmentID, GL20.GL_COMPILE_STATUS);
        if(compileStatus == GL20.GL_FALSE) {
            int length = GL20.glGetShaderi(fragmentID, GL20.GL_INFO_LOG_LENGTH);
            Log.error(fragmentFilepath + "\n\tFragment shader compilation failed!");
            Log.error(GL20.glGetShaderInfoLog(fragmentID, length));
            System.exit(-1);
        }

        // Link shaders and check for linking errors
        shaderProgramID = GL20.glCreateProgram();
        GL20.glAttachShader(shaderProgramID, vertexID);
        GL20.glAttachShader(shaderProgramID, fragmentID);

        GL20.glLinkProgram(shaderProgramID);
        compileStatus = GL20.glGetProgrami(shaderProgramID, GL30.GL_LINK_STATUS);
        if(compileStatus == GL20.GL_FALSE) {
            int length = GL20.glGetProgrami(shaderProgramID, GL20.GL_INFO_LOG_LENGTH);
            Log.error(shaderLocation + "\n\tLinking of shaders failed!");
            Log.error(GL20.glGetProgramInfoLog(shaderProgramID, length));
            System.exit(-1);
        }
    }

    public void bind() {
        if(!currentlyInUse) GL30.glUseProgram(shaderProgramID);
        currentlyInUse = true;
    }

    public void unbind() {
        GL30.glUseProgram(0);
        currentlyInUse = false;
    }

    public void uploadMat4f(String varName, Matrix4f mat4) {
        int varLocation = GL30.glGetUniformLocation(shaderProgramID, varName);
        this.bind();
        FloatBuffer matBuffer = BufferUtils.createFloatBuffer(16);
        mat4.get(matBuffer);
        GL30.glUniformMatrix4fv(varLocation, false, matBuffer);
    }

    public void uploadIntArray(String varName, int[] array) {
        int varLocation = GL30.glGetUniformLocation(shaderProgramID, varName);
        this.bind();
        GL30.glUniform1iv(varLocation, array);
    }
}
