package com.harmonygames.harmonyengine.utils;

import com.harmonygames.harmonyengine.Log;
import com.harmonygames.harmonyengine.render.Shader;

import java.io.File;
import java.util.HashMap;

public class Assets {

    private static final HashMap<String, Shader> shaders = new HashMap<>();

    public static Shader loadShader(String filePath) {
        File file = new File(filePath);
        if(!file.exists()) {
            Log.fatalError("Could not load the shader with a file path of: '" + file.getAbsolutePath() + "'");
        }

        if(shaders.containsKey(file.getAbsolutePath())) return shaders.get(file.getAbsolutePath());

        if(!file.exists()) {
            Log.fatalError("File path of '" + file.getAbsolutePath() + "' does not exist!!!" +
                    "\n\tPlease make sure that you are referencing a shader directory location that exists!");
        }

        if(!file.isDirectory()) {
            Log.warn("File path of '" + file.getAbsolutePath() + "' is not a directory that contains shaders!!!" +
                    "\n\tThis will most likely result in an error later on!!");
        }

        File[] shaderFiles = file.listFiles();
        if(shaderFiles == null) {
            Log.fatalError("Children shader files of '" + file.getAbsolutePath() + "' came back as a null array!!" +
                    "\n\tPlease make sure the location is a directory and it contains both at least a fragment and shader glsl file");
            return null;
        }

        Shader shader = new Shader(shaderFiles);
        shaders.put(file.getAbsolutePath(), shader);

        return shader;
    }

}
