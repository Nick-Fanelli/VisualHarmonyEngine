package com.harmonygames.harmonyengine.utils;

import com.harmonygames.harmonyengine.Log;
import com.harmonygames.harmonyengine.render.Shader;

import java.io.File;
import java.util.HashMap;

public class Assets {

    private static final HashMap<String, Shader> shaders = new HashMap<>();

    public static Shader getShader(String directoryLocation) {
        File file = new File(directoryLocation);

        if(!file.isDirectory()) {
            Log.warn("Shader requested directory of '" + file.getAbsolutePath() + "' is not a directory!!!");
        }

        if(!file.exists()) {
            Log.fatalError("Shader requested directory of '" + file.getAbsolutePath() + "' does not exist!");
            System.exit(-1);
        }

        if(shaders.containsKey(file.getAbsolutePath())) return shaders.get(file.getAbsolutePath());

        Shader shader = new Shader(file);
        shader.compile();
        shaders.put(file.getAbsolutePath(), shader);
        return shader;
    }

}
