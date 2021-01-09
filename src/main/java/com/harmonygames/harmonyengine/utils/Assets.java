package com.harmonygames.harmonyengine.utils;

import com.harmonygames.harmonyengine.render.Shader;

import java.util.HashMap;

public class Assets {

    private static final HashMap<String, Shader> shaders = new HashMap<>();

    public static Shader loadShader(String filePath) {
        if(!filePath.startsWith("/")) filePath = "/" + filePath;

        if(shaders.containsKey(filePath)) return shaders.get(filePath);

        Shader shader = new Shader(filePath, FileUtils.readFromFile(filePath));
        shaders.put(filePath, shader);

        return shader;
    }

}
